#include "server.h"

static t_bool		args_are_valid(char **args)
{
	int		arg_int;

	if (ft_strcmp(args[0], "1") != 0 && ft_strcmp(args[0], "2") != 0)
		return (FALSE);
	if (ft_is_int(args[2]) == FALSE)
		return (FALSE);
	arg_int = ft_atoi(args[2]);
	if (arg_int < 0 || arg_int > USHRT_MAX)
		return (FALSE);
	return (TRUE);
}

static t_ex_ret		connect_according_to_af(char *type, char *addr,
						uint16_t port, int sock)
{
	struct sockaddr_in	sin;
	struct sockaddr_in6	sin6;

	if (ft_strcmp(type, "2") == 0)
	{
		sin6.sin6_family = AF_INET6;
		sin6.sin6_port = htons(port);
		if (inet_pton(AF_INET6, addr, &sin6.sin6_addr) != 1)
			return (print_and_return_failure(INET_PTON_ERR));
		if ((connect(sock, (const struct sockaddr *)&sin6, sizeof(sin6))) == -1)
			return (print_and_return_failure(CONNECT_ERR));
	}
	else
	{
		sin.sin_family = AF_INET;
		sin.sin_port = htons(port);
		if ((sin.sin_addr.s_addr = inet_addr(addr)) == INADDR_NONE)
			return (print_and_return_failure(INET_ADDR_ERR));
		if ((connect(sock, (const struct sockaddr *)&sin, sizeof(sin))) == -1)
			return (print_and_return_failure(CONNECT_ERR));
	}
	return (SUCCESS);
}

static int			connect_to_user(char *type, char *addr, uint16_t port)
{
	int					sock;
	struct protoent		*proto;

	if ((proto = getprotobyname(TCP_PROTONAME)) == NULL)
	{
		print_debug_output(NULL, 0, PROTOBYNAME_ERR, NULL);
		return (-1);
	}
	if ((sock = socket((ft_strcmp(type, "2") == 0 ? PF_INET6 : PF_INET),
						SOCK_STREAM, proto->p_proto)) < 0)
	{
		print_debug_output(NULL, 0, SOCKET_ERR, NULL);
		return (-1);
	}
	if (connect_according_to_af(type, addr, port, sock) == FAILURE)
		return (-1);
	return (sock);
}

static char			**get_arg_tab(char *cmd)
{
	char		**cmd_args;
	char		**arg_tab;

	cmd_args = ft_strsplit(cmd, ' ');
	if (!cmd_args || ft_tablen(cmd_args) != 2)
	{
		ft_tabdel(&cmd_args);
		return (NULL);
	}
	arg_tab = ft_strsplit(cmd_args[1], cmd_args[1][0]);
	ft_tabdel(&cmd_args);
	if (!arg_tab || ft_tablen(arg_tab) != 3 || args_are_valid(arg_tab) == FALSE)
	{
		ft_tabdel(&arg_tab);
		return (NULL);
	}
	return (arg_tab);
}

void				exec_eprt_cmd(t_user *user, char *cmd)
{
	char		**arg_tab;

	if ((arg_tab = get_arg_tab(cmd)) == NULL)
	{
		send_oneline_reply_to_user(user, RES_501);
		return ;
	}
	user->dt_port = ft_atoi(arg_tab[2]);
	print_debug_output("Trying to connect to port", user->dt_port,
		"on address", arg_tab[1]);
	user->dt_client_sock = connect_to_user(arg_tab[0], arg_tab[1],
								user->dt_port);
	if (user->dt_client_sock == -1)
		send_oneline_reply_to_user(user, RES_425);
	else
	{
		print_data_output("Connection etablished with user's port",
			user->dt_port, ": DT channel created [ACTIVE MODE]", NULL);
		send_oneline_reply_to_user(user, RES_200);
		user->mode = ACTIVE;
	}
	ft_tabdel(&arg_tab);
}
