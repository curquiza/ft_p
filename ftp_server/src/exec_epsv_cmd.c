#include "server.h"

static void		send_epsv_response(t_user *user, int addr)
{
	char		*response;
	char		*tmp_int;

	(void)addr;
	tmp_int = ft_itoa(user->dt_port);
	response = ft_strjoin3("229 Entering extended passive mode (|||",
		tmp_int, "|)");
	free(tmp_int);
	send_oneline_reply_to_user(user, response);
	free(response);
}

static t_ex_ret	get_user_dt_port(t_user *user, int sock)
{
	uint16_t			port;

	port = PORT_MIN_RANGE;
	while (port <= PORT_MAX_RANGE)
	{
		print_debug_output("Testing port", port, "for DT channel...", NULL);
		if (bind_server(sock, port) == SUCCESS)
		{
			user->dt_port = port;
			print_debug_output("Available port found :", port, NULL, NULL);
			return (SUCCESS);
		}
		port++;
	}
	return (FAILURE);
}

static int		socket_according_to_af(void)
{
	int					sock;
	struct protoent		*proto;

	sock = -1;
	if ((proto = getprotobyname(TCP_PROTONAME)) == NULL)
		return (ret_err_neg(PROTOBYNAME_ERR));
	if (g_addr_family == AF_INET6)
	{
		if ((sock = socket(PF_INET6, SOCK_STREAM, proto->p_proto)) == -1)
			return (ret_err_neg(SOCKET_ERR));
	}
	else
	{
		if ((sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)) == -1)
			return (ret_err_neg(SOCKET_ERR));
	}
	return (sock);
}

static int		create_server_socket_on_valid_port(t_user *user)
{
	int					sock;

	if ((sock = socket_according_to_af()) == -1)
	{
		print_debug_output(NULL, 0, SOCKET_ERR, NULL);
		return (-1);
	}
	if (get_user_dt_port(user, sock) == FAILURE)
	{
		print_debug_output(NULL, 0, NO_PORT_ERR, NULL);
		return (-1);
	}
	if (listen(sock, LISTEN_NB) == -1)
	{
		print_debug_output(NULL, 0, LISTEN_ERR, NULL);
		return (-1);
	}
	return (sock);
}

void			exec_epsv_cmd(t_user *user, char *cmd)
{
	if (cmd_has_no_arg(user, cmd) == FALSE)
		return ;
	if ((user->dt_server_sock = create_server_socket_on_valid_port(user)) == -1)
	{
		send_oneline_reply_to_user(user, RES_425);
		return ;
	}
	print_data_output("Socket server listening on port", user->dt_port,
		NULL, NULL);
	send_epsv_response(user, DEFAULT_SIN_ADDR);
	if (accept_according_to_af(user) == FAILURE)
	{
		print_debug_output(NULL, 0, ACCEPT_ERR, NULL);
		send_oneline_reply_to_user(user, RES_425);
		return ;
	}
	print_data_output("Connection accepted on port", user->dt_port,
		": DT channel created [PASSIVE MODE]", NULL);
	user->mode = PASSIVE;
}
