#include "server.h"

void		transit_file(int client_sock)
{
	struct stat		stat_struct;
	int				size;
	t_byte			*ptr;

	int fd = open("test/input/package-lock.json", O_RDONLY);
	fstat(fd, &stat_struct);
	size = stat_struct.st_size;
	// ft_printf("size = %d\n", size);
	ptr = NULL;
	ptr = mmap(ptr, size, PROT_READ, MAP_PRIVATE, fd, 0);
	int s = send(client_sock, ptr, size, 0);
	// int s = write(client_sock, ptr, size);
	ft_printf("Sending file...\n");
	ft_printf("send return = %d\n", s);
	close(fd);
}

void		exec_ls(int client_sock)
{
	char	*args[3] = { "/bin/ls", "-la", NULL };
	pid_t	pid;
	// int		status;

	pid = fork();
	if (pid == 0)
	{
		dup2(client_sock, STDOUT_FILENO);
		execv(args[0], args); // END OF CHILD PROCESS
		ft_dprintf(STDERR_FILENO, "Error during execv\n");
		exit(1);
	}
	else
	{
		// wait4(0, &status, 0, NULL);
		// ft_printf("pid = %d - status = %d\n", pid, status);
	}
}

static void	communicate_with_new_client(int client_sock)
{
	char	cmd[1024];
	int		len;

	while ((len = recv(client_sock, &cmd, 1023, 0)) > 0)
	{
		cmd[len] = '\0';
		ft_printf("------------------\nClient command = %s", cmd);

		if (ft_strcmp(cmd, "GET\n") == 0)
			transit_file(client_sock);
		else if (ft_strcmp(cmd, "LS\n") == 0)
			exec_ls(client_sock);
		else
			send(client_sock, "RECU !\n", 7, 0);
	}
}

void		listen_to_clients(int server_sock)
{
	pid_t				pid;
	int					client_sock;
	unsigned int		client_size;
	struct sockaddr_in	client_sin;
	int					client_num;

	client_num = 1;
	while (1)
	{
		client_sock = accept(server_sock, (struct sockaddr *)&client_sin, &client_size);
		pid = fork();
		if (pid == 0)
		{
			child_signals_handler();
			ft_printf("------------------\nClient number %d connected\n", client_num);
			communicate_with_new_client(client_sock);
			ft_printf("Client number %d has quit...\n", client_num);
			close(client_sock);
		}
		else
		{
			close(client_sock);
		}
		client_num++;
	}
}
