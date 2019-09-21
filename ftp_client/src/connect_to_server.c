#include "client.h"

static t_ex_ret		print_and_return_failure(char *str)
{
	ft_dprintf(2, "%s\n", str);
	return (FAILURE);
}

static int		ret_err_neg(char *s)
{
	ft_dprintf(2, "Error: %s\n", s);
	return (-1);
}

static t_ex_ret		connect_according_to_af(char *addr, uint16_t port, int sock)
{
	struct sockaddr_in	sin;
	struct sockaddr_in6	sin6;

	if (g_addr_family == AF_INET6)
	{
		sin6.sin6_family = AF_INET6;
		sin6.sin6_port = htons(port);
		if (inet_pton(AF_INET6, addr, &sin6.sin6_addr) == 0)
			return (print_and_return_failure(INET_ERR));
		if ((connect(sock, (const struct sockaddr *)&sin6, sizeof(sin6))) == -1)
			return (print_and_return_failure(CONNECT_ERR));
	}
	else
	{
		sin.sin_family = AF_INET;
		sin.sin_port = htons(port);
		if ((sin.sin_addr.s_addr = inet_addr(addr)) == 0)
			return (print_and_return_failure(INET_ERR));
		if ((connect(sock, (const struct sockaddr *)&sin, sizeof(sin))) == -1)
			return (print_and_return_failure(CONNECT_ERR));
	}
	return (SUCCESS);
}

int		connect_to_server(char *addr, uint16_t port)
{
	int					sock;
	struct protoent		*proto;

	if ((proto = getprotobyname("tcp")) == NULL)
		return (ret_err_neg("During getprotobyname"));
	if ((sock = socket((g_addr_family == AF_INET6 ? PF_INET6 : PF_INET),
			SOCK_STREAM, proto->p_proto)) < 0)
		return (ret_err_neg(SOCKET_ERR));
	if (connect_according_to_af(addr, port, sock) == FAILURE)
		return (-1);
	return (sock);
}
