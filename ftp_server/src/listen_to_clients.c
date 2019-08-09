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
	close(fd);
}

static void	close_user_data_channel(t_user *user)
{
	close(user->dt_client_sock);
	close(user->dt_server_sock);
	user->dt_client_sock = -1;
	user->dt_server_sock = -1;
}

void		exec_ls(t_user *user)
{
	char	*args[3] = { "/bin/ls", "-l", NULL };
	pid_t	pid;

	// si pas de DT channel, envoyer une reply.
	pid = fork();
	if (pid == 0)
	{
		send_oneline_reply_to_user(user->cmd_client_sock, user->num, RES_125);
		dup2(user->dt_client_sock, STDOUT_FILENO);	// PAS LE BON CANAL
		execv(args[0], args);
		ft_dprintf(STDERR_FILENO, "Error during execv\n");
		exit(1);
	}
	else
	{
		wait4(0, NULL, 0, NULL);
		print_verbose_sis("Sent to Client", user->num, ": * LS output *");
		close_user_data_channel(user);
		send_oneline_reply_to_user(user->cmd_client_sock, user->num, RES_226);
	}
}

static char		*get_pasv_response(int addr, uint16_t port)
{
	char	*s;
	t_byte		p1;
	t_byte		p2;

	(void)addr;
	p2 = (t_byte)(port & 0x00ff);
	p1 = (t_byte)((port >> 8) & 0x00ff);
	asprintf(&s, "227 Entering Passive Mode (0,0,0,0,%hhu,%hhu)", p1, p2); // !!!

	return (s);
}

static void		passif_mode(t_user *user)
{
	uint16_t			port;
	char				*response;
	unsigned int		dt_size;
	struct sockaddr_in	dt_sin;

	user->dt_server_sock = create_socket_server_on_random_port(&port);
	if (user->dt_server_sock == -1)
		return ; // envoyer message error vers client
	response = get_pasv_response(DEF_SIN_ADDR, port);
	send_oneline_reply_to_user(user->cmd_client_sock, user->num, response);

	user->dt_client_sock = accept(user->dt_server_sock, (struct sockaddr *)&dt_sin, &dt_size);
	if (user->dt_client_sock < 0)
		ft_dprintf(2, "Impossible to accept connection for DT\n");
	free(response);
}

static void		communicate_with_new_user(t_user *user)
{
	char	cmd[1024];
	int		len;

	send_oneline_reply_to_user(user->cmd_client_sock, user->num, RES_220);
	while ((len = recv(user->cmd_client_sock, &cmd, 1024, 0)) > 0)
	{
		if (len >= 2 && cmd[len - 2] == '\r')
			cmd[len - 2] = '\0';
		else if (len >= 1 && cmd[len - 1] == '\n')
			cmd[len - 1] = '\0';
		print_verbose_siss("Got from Client", user->num, ":", cmd);
		if (ft_strcmp(cmd, "GET") == 0)
			transit_file(user->cmd_client_sock);
		else if (ft_strcmp(cmd, "LIST") == 0)
			exec_ls(user);
		else if (ft_strcmp(cmd, "QUIT") == 0)
			break ;
		else if (ft_strcmp(cmd, "PASV") == 0)
			passif_mode(user);
		else
			send(user->cmd_client_sock, "RECU !\n", 7, 0);
	}
}

static void	init_new_user(t_user *user, int cmd_client_sock, int user_num)
{
	user->num = user_num;
	user->cmd_client_sock = cmd_client_sock;
	user->dt_server_sock = -1;
	user->dt_client_sock = -1;
}

t_ex_ret	listen_to_clients(int server_sock)
{
	pid_t				pid;
	int					cmd_client_sock;
	unsigned int		client_size;
	struct sockaddr_in	client_sin;
	int					num;
	t_user				user;

	num = 1;
	while (1)
	{
		cmd_client_sock = accept(server_sock, (struct sockaddr *)&client_sin, &client_size);
		if (cmd_client_sock < 0)
			return (ft_ret_err("During accept"));
		if ((pid = fork()) < 0)
			return (ft_ret_err("During fork"));
		if (pid == 0)
		{
			child_signals_handler();
			print_verbose_sis("Client", num, "connected");
			init_new_user(&user, cmd_client_sock, num);
			communicate_with_new_user(&user);
			print_verbose_sis("Client", num, "has quit...");
			close(cmd_client_sock);
			exit(0);
		}
		else
		{
			close(cmd_client_sock);
		}
		num++;
	}
	return (SUCCESS);
}
