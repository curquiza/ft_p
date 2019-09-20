#include "server.h"

static t_bool	args_are_valid(char **args)
{
	int		arg_int;

	while (*args)
	{
		if (ft_is_int(*args) == FALSE)
			return (FALSE);
		arg_int = ft_atoi(*args);
		if (arg_int < 0 || arg_int > UCHAR_MAX)
			return (FALSE);
		args++;
	}
	return (TRUE);
}

static void		get_addr(char **args, char *addr)
{
	int		len;

	ft_strcpy(addr, args[0]);
	len = ft_strlen(args[0]) + 1;
	addr[len - 1] = '.';
	ft_strcpy(addr + len, args[1]);
	len += ft_strlen(args[1]) + 1;
	addr[len - 1] = '.';
	ft_strcpy(addr + len, args[2]);
	len += ft_strlen(args[2]) + 1;
	addr[len - 1] = '.';
	ft_strcpy(addr + len, args[3]);
	len += ft_strlen(args[3]);
	addr[len] = 0;
}

static uint16_t	get_port(char **args)
{
	uint16_t	addr;
	int			tmp;

	addr = 0;
	tmp = ft_atoi(args[4]);
	addr = (tmp & 0x000000ff);
	addr = addr << 8;
	tmp = ft_atoi(args[5]);
	addr |= (tmp & 0x000000ff);
	return (addr);
}

static int		connect_to_user(char *addr, uint16_t port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	if ((proto = getprotobyname(TCP_PROTONAME)) == NULL)
	{
		print_debug_output(NULL, 0, PROTOBYNAME_ERR, NULL);
		return (-1);
	}
	if ((sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)) < 0)
	{
		print_debug_output(NULL, 0, SOCKET_ERR, NULL);
		return (-1);
	}
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	if ((sin.sin_addr.s_addr = inet_addr(addr)) == 0)
	{
		print_debug_output(NULL, 0, INET_ERR, NULL);
		return (-1);
	}
	if ((connect(sock, (const struct sockaddr *)&sin, sizeof(sin))) == -1)
	{
		print_debug_output(NULL, 0, CONNECT_ERR, NULL);
		return (-1);
	}
	return (sock);
}

static char		**get_arg_tab(char *cmd)
{
	char		**cmd_args;
	char		**arg_tab;

	cmd_args = ft_strsplit(cmd, ' ');
	if (!cmd_args || ft_tablen(cmd_args) != 2)
	{
		ft_tabdel(&cmd_args);
		return (NULL);
	}
	arg_tab = ft_strsplit(cmd_args[1], ',');
	ft_tabdel(&cmd_args);
	if (!arg_tab || ft_tablen(arg_tab) != 6 || args_are_valid(arg_tab) == FALSE)
	{
		ft_tabdel(&arg_tab);
		return (NULL);
	}
	return (arg_tab);
}

void			exec_port_cmd(t_user *user, char *cmd)
{
	char		**arg_tab;
	char		addr[15];

	if ((arg_tab = get_arg_tab(cmd)) == NULL)
	{
		send_oneline_reply_to_user(user, RES_501);
		return ;
	}
	get_addr(arg_tab, addr);
	user->dt_port = get_port(arg_tab);
	ft_tabdel(&arg_tab);
	print_debug_output("Trying to connect to port", user->dt_port,
		"on address", addr);
	user->dt_client_sock = connect_to_user(addr, user->dt_port);
	if (user->dt_client_sock == -1)
		send_oneline_reply_to_user(user, RES_425);
	else
	{
		print_data_output("Connection etablished with user's port",
			user->dt_port, ": DT channel created [ACTIVE MODE]", NULL);
		send_oneline_reply_to_user(user, RES_200);
		user->mode = ACTIVE;
	}
}
