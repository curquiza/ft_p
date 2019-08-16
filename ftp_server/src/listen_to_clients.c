#include "server.h"

t_cmd	g_cmd_tab[CMD_NB] =
{
	{ "PASV", &exec_pasv_cmd },
	{ "PORT", &exec_port_cmd },
	{ "LIST", &exec_list_cmd },
	{ "GET", &exec_get_cmd }
};

static char		*get_cmd_name(char *cmd)
{
	int		i;
	char	*cmd_name;

	i = 0;
	while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\n' && cmd[i] != '\r')
		i++;
	cmd_name = ft_strnew(i);
	if (cmd_name == NULL)
		ft_exit(MALLOC_ERR, 1);
	ft_memmove(cmd_name, cmd, i);
	return (cmd_name);
}

static void		exec_cmd(t_user *user, char *cmd)
{
	int		i;
	char	*cmd_name;

	i = 0;
	cmd_name = get_cmd_name(cmd);
	while (i < CMD_NB)
	{
		if (ft_strcmp(cmd_name, g_cmd_tab[i].name) == 0)
		{
			g_cmd_tab[i].f(user, cmd);
			free(cmd_name);
			return ;
		}
		i++;
	}
	free(cmd_name);
	send_oneline_reply_to_user(user->ctrl_client_sock, user->num, RES_500);
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
		if (ft_strcmp(cmd, "QUIT") == 0)
			break ;
		exec_cmd(user, cmd);
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
