#include "client.h"

t_ex_ret		bind_server(int sock, uint16_t port)
{
	struct sockaddr_in	sin;
	struct sockaddr_in6	sin6;

	if (g_client.addr_family == AF_INET6)
	{
		sin6.sin6_family = AF_INET6;
		sin6.sin6_port = htons(port);
		sin6.sin6_addr = DEFAULT_SIN6_ADDR;
		if (bind(sock, (const struct sockaddr *)&sin6, sizeof(sin6)) == -1)
			return (FAILURE);
	}
	else
	{
		sin.sin_family = AF_INET;
		sin.sin_port = htons(port);
		sin.sin_addr.s_addr = DEFAULT_SIN_ADDR;
		if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
			return (FAILURE);
	}
	return (SUCCESS);
}


static t_ex_ret	get_user_dt_port(uint16_t *dt_port, int sock)
{
	uint16_t			port;

	port = PORT_MIN_RANGE;
	while (port <= PORT_MAX_RANGE)
	{
		if (bind_server(sock, port) == SUCCESS)
		{
			*dt_port = port;
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
		return (print_and_return_neg(PROTOBYNAME_ERR));
	if (g_client.addr_family == AF_INET6)
	{
		if ((sock = socket(PF_INET6, SOCK_STREAM, proto->p_proto)) == -1)
			return (print_and_return_neg(SOCKET_ERR));
	}
	else
	{
		if ((sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)) == -1)
			return (print_and_return_neg(SOCKET_ERR));
	}
	return (sock);
}

int				create_server_socket_on_valid_port(uint16_t *dt_port)
{
	int					sock;

	if ((sock = socket_according_to_af()) == -1)
		return (print_and_return_neg(DATA_CONN_ERR));
	if (get_user_dt_port(dt_port, sock) == FAILURE)
		return (print_and_return_neg(DATA_CONN_ERR));
	if (listen(sock, LISTEN_NB) == -1)
		return (print_and_return_neg(DATA_CONN_ERR));
	return (sock);
}
