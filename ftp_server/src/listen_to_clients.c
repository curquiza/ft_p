#include "server.h"

t_cmd	g_cmd_tab[CMD_NB] =
{
	{ "PASV", &exec_pasv_cmd },
	{ "EPSV", &exec_epsv_cmd },
	{ "PORT", &exec_port_cmd },
	{ "EPRT", &exec_eprt_cmd },
	{ "LIST", &exec_list_cmd },
	{ "PWD", &exec_pwd_cmd },
	{ "CWD", &exec_cwd_cmd },
	{ "RETR", &exec_retr_cmd },
	{ "STOR", &exec_stor_cmd },
	{ "TYPE", &exec_type_cmd }
};

static void	init_new_user(t_user *user, int ctrl_client_sock, int user_num)
{
	user->num = user_num;
	user->ctrl_client_sock = ctrl_client_sock;
	user->dt_server_sock = -1;
	user->dt_client_sock = -1;
	user->dt_port = 0;
	user->mode = NONE;
}

static void	child_process(int num, int ctrl_client_sock)
{
	t_user				user;

	child_signals_handler();
	init_new_user(&user, ctrl_client_sock, num);
	print_ctrl_output("Client", num, "connected", NULL);
	g_user_nb++;
	print_debug_output("Number of users currently connected :", g_user_nb,
			NULL, NULL);
	if (g_user_nb > MAX_USERS)
	{
		send_oneline_reply_to_user(&user, RES_550_4);
		print_ctrl_output("Client", num, "was disconnected", NULL);
		return ;
	}
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
		ctrl_client_sock = accept(server_sock,
			(struct sockaddr *)&client_sin, &client_size);
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
			close(ctrl_client_sock);
		g_user_nb++;
		num++;
	}
	return (SUCCESS);
}
