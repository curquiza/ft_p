#include "client.h"

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

static char		**get_connection_args(char *cmd)
{
	char	**first_split;
	char	**conn_args;

	first_split = ft_strsplit(cmd, '(');
	if (!first_split || ft_tablen(first_split) != 2)
	{
		ft_tabdel(&first_split);
		return (NULL);
	}
	first_split[1][ft_strlen(first_split[1]) - 1] = '\0';
	conn_args = ft_strsplit(first_split[1], ',');
	if (!conn_args || ft_tablen(conn_args) != 6
		|| args_are_valid(conn_args) == FALSE)
	{
		ft_tabdel(&conn_args);
		return (NULL);
	}
	return (conn_args);
}

static int		print_and_ret_neg(char *str)
{
	ft_printf("%s\n", str);
	return (-1);
}

static int		connect_to_user(char *addr, uint16_t port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	if ((proto = getprotobyname(TCP_PROTONAME)) == NULL)
		print_and_ret_neg(PROTOBYNAME_ERR);
	if ((sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)) < 0)
		print_and_ret_neg(SOCKET_ERR);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	if ((sin.sin_addr.s_addr = inet_addr(addr)) == INADDR_NONE)
		print_and_ret_neg(INET_ADDR_ERR);
	if ((connect(sock, (const struct sockaddr *)&sin, sizeof(sin))) == -1)
		print_and_ret_neg(CONNECT_ERR);
	return (sock);
}

static void	ask_for_data_connection(void)
{
	char	*line_to_send;

	if (g_mode == PASSIVE)
		line_to_send = ft_strdup(g_addr_family == AF_INET6 ? "EPSV" : "PASV");
	else
		line_to_send = NULL;
	send_to_server(line_to_send);
	free(line_to_send);
}

int		etablish_data_connection()
{
	char		reply_buff[REPLY_MAX_SIZE];
	char		**conn_args;
	char		addr[15];
	uint16_t	dt_port;
	int			dt_client_sock;

	// line_to_send = data_connection_command();
	// send_to_server(line_to_send);
	// free(line_to_send);
	ask_for_data_connection();
	if (parse_and_display_reply(reply_buff) != 0
		|| !(conn_args = get_connection_args(reply_buff)))
	{
		ft_printf("%s\n", DATA_CONN_ERR);
		return (-1);
	}
	get_addr(conn_args, addr);
	dt_port = get_port(conn_args);
	ft_tabdel(&conn_args);
	dt_client_sock = connect_to_user(addr, dt_port);
	if (dt_client_sock == -1)
	{
		ft_printf("%s\n", DATA_CONN_ERR);
		return (-1);
	}
	return (dt_client_sock);
}
