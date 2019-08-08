#include "server.h"

void		transit_file(int client_sock)
{
	struct stat		stat_struct;
	int				size;
	t_byte			*ptr;

	int fd = open("test/input/package-lock.json", O_RDONLY);
	fstat(fd, &stat_struct);
	size = stat_struct.st_size;
	ptr = NULL;
	ptr = mmap(ptr, size, PROT_READ, MAP_PRIVATE, fd, 0);
	send(client_sock, ptr, size, 0);
	// write(client_sock, ptr, size);
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

static void	communicate_with_new_client(int client_sock, int client_num)
{
	char	cmd[1024];
	int		len;

	while ((len = recv(client_sock, &cmd, 1023, 0)) > 0)
	{
		cmd[len - 1] = '\0';
		print_verbose_siss("Client", client_num, "command :", cmd);
		if (ft_strcmp(cmd, "GET") == 0)
			transit_file(client_sock);
		else if (ft_strcmp(cmd, "LS") == 0)
			exec_ls(client_sock);
		else if (ft_strcmp(cmd, "QUIT") == 0)
			break ;
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
			print_verbose_sis("Client", client_num, "connected");
			communicate_with_new_client(client_sock, client_num);
			print_verbose_sis("Client", client_num, "has quit...");
			close(client_sock);
			exit(0);
		}
		else
		{
			close(client_sock);
		}
		client_num++;
	}
}
