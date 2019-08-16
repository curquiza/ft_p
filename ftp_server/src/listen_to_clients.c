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
	print_data_output("Closing DT channel on port", user->dt_port, NULL, NULL);
	close(user->dt_client_sock);
	close(user->dt_server_sock);
	user->dt_client_sock = -1;
	user->dt_server_sock = -1;
}

void		exec_ls(t_user *user)
{
	char	*args[3] = { "/bin/ls", "-l", NULL };
	pid_t	pid;

	if (user->dt_client_sock == -1)
	{
		send_oneline_reply_to_user(user->ctrl_client_sock, user->num, RES_426);
		return ;
	}
	if ((pid = fork()) < 0)
	{
		send_oneline_reply_to_user(user->ctrl_client_sock, user->num, RES_451);
		return ;
	}
	if (pid == 0)
	{
		send_oneline_reply_to_user(user->ctrl_client_sock, user->num, RES_125);
		dup2(user->dt_client_sock, STDOUT_FILENO);	// PAS LE BON CANAL
		execv(args[0], args);
		ft_dprintf(STDERR_FILENO, "Error during execv\n");
		exit(1);
	}
	else
	{
		wait4(0, NULL, 0, NULL);
		print_data_output("--> Sent in DT channel on port", user->dt_port, ": * LS output *", NULL);
		close_user_data_channel(user);
		send_oneline_reply_to_user(user->ctrl_client_sock, user->num, RES_226);
	}
}

static char		*get_pasv_response(int addr, uint16_t port)
{
	char		*s;
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

	user->dt_server_sock = create_server_socket_on_random_port(&port);
	if (user->dt_server_sock == -1)
		return ; // send error reply to user
	user->dt_port = port;
	print_data_output("Socket server listening on port", user->dt_port, NULL, NULL);
	response = get_pasv_response(DEF_SIN_ADDR, port);
	send_oneline_reply_to_user(user->ctrl_client_sock, user->num, response);

	user->dt_client_sock = accept(user->dt_server_sock, (struct sockaddr *)&dt_sin, &dt_size);
	if (user->dt_client_sock < 0)
		return ; // send error reply to user
	print_data_output("Connection accepted on port", user->dt_port, ": DT channel created", NULL);
	free(response);
}

static void		communicate_with_new_user(t_user *user)
{
	char	cmd[1024];
	int		len;

	send_oneline_reply_to_user(user->ctrl_client_sock, user->num, RES_220);
	while ((len = recv(user->ctrl_client_sock, &cmd, 1024, 0)) > 0)
	{
		if (len >= 2 && cmd[len - 2] == '\r')
			cmd[len - 2] = '\0';
		else if (len >= 1 && cmd[len - 1] == '\n')
			cmd[len - 1] = '\0';
		print_ctrl_output("<-- Received from Client", user->num, ":", cmd);
		if (ft_strcmp(cmd, "GET") == 0)
			transit_file(user->ctrl_client_sock);
		else if (ft_strcmp(cmd, "LIST") == 0)
			exec_ls(user);
		else if (ft_strcmp(cmd, "QUIT") == 0)
			break ;
		else if (ft_strcmp(cmd, "PASV") == 0)
			passif_mode(user);
		else
			send_oneline_reply_to_user(user->ctrl_client_sock, user->num, RES_500);
	}
}

static void	init_new_user(t_user *user, int ctrl_client_sock, int user_num)
{
	user->num = user_num;
	user->ctrl_client_sock = ctrl_client_sock;
	user->dt_server_sock = -1;
	user->dt_client_sock = -1;
	user->dt_port = -1;
}

static void	child_process(int num, int ctrl_client_sock)
{
	t_user				user;

	child_signals_handler();
	print_ctrl_output("Client", num, "connected", NULL);
	init_new_user(&user, ctrl_client_sock, num);
	communicate_with_new_user(&user);
	print_ctrl_output("Client", num, "has quit", NULL);
	close(ctrl_client_sock);
}

t_ex_ret	listen_to_clients(int server_sock)
{
	pid_t				pid;
	int					num;
	int					ctrl_client_sock;
	unsigned int		client_size;
	struct sockaddr_in	client_sin;

	num = 1;
	while (1)
	{
		ctrl_client_sock = accept(server_sock, (struct sockaddr *)&client_sin, &client_size);
		if (ctrl_client_sock < 0)
			return (ft_ret_err("During accept"));
		if ((pid = fork()) < 0)
			return (ft_ret_err("During fork"));
		if (pid == 0)
		{
			child_process(num, ctrl_client_sock);
			exit(0);
		}
		else
		{
			close(ctrl_client_sock);
		}
		num++;
	}
	return (SUCCESS);
}
