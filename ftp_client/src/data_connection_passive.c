#include "client.h"

static char		*get_addr(char **args)
{
	int		i;
	char	*final_addr;

	if (g_client.addr_family == AF_INET6)
		return (ft_strdup(g_client.addr));
	final_addr = ft_strdup(args[0]);
	i = 0;
	while (final_addr[i])
	{
		if (final_addr[i] == ',')
			final_addr[i] = '.';
		i++;
	}
	return (final_addr);
}

static uint16_t	get_port(char **args)
{
	uint16_t	addr;
	int			tmp;

	if (g_client.addr_family == AF_INET6)
		return (ft_atoi(args[1]));
	addr = 0;
	tmp = ft_atoi(args[4]);
	addr = (tmp & 0x000000ff);
	addr = addr << 8;
	tmp = ft_atoi(args[5]);
	addr |= (tmp & 0x000000ff);
	return (addr);
}

static t_ex_ret	connect_according_to_af(char *addr, uint16_t port, int sock)
{
	struct sockaddr_in	sin;
	struct sockaddr_in6	sin6;

	if (g_client.addr_family == AF_INET6)
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

static int		connect_to_user(char *addr, uint16_t port)
{
	int					sock;
	struct protoent		*proto;

	if ((proto = getprotobyname(TCP_PROTONAME)) == NULL)
	{
		ft_printf("%s\n", PROTOBYNAME_ERR);
		return (-1);
	}
	if ((sock = socket(g_client.addr_family, SOCK_STREAM, proto->p_proto)) < 0)
	{
		ft_printf("%s\n", SOCKET_ERR);
		return (-1);
	}
	if (connect_according_to_af(addr, port, sock) == FAILURE)
		return (-1);
	return (sock);
}


t_ex_ret		etablish_data_connection_passive(t_dt_socks *dt)
{
	char		reply_buff[REPLY_MAX_SIZE];
	char		**conn_args;
	uint16_t	dt_port;
	// int			dt_client_sock;
	char		*addr;

	send_to_server(g_client.addr_family == AF_INET6 ? "EPSV" : "PASV");
	if (parse_and_display_reply(reply_buff) != 0
		|| !(conn_args = get_connection_args_passive(reply_buff)))
		return (print_and_return_failure(DATA_CONN_ERR));
	addr = get_addr(conn_args);
	dt_port = get_port(conn_args);
	ft_tabdel(&conn_args);
	dt->client_sock = connect_to_user(addr, dt_port);
	free(addr);
	if (dt->client_sock == -1)
		return (print_and_return_failure(DATA_CONN_ERR));
	return (SUCCESS);
}
