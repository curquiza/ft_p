#include "client.h"

static t_ex_ret	print_and_return_failure(char *str)
{
	ft_dprintf(2, "%s\n", str);
	return (FAILURE);
}

static int		ret_err_neg(char *s)
{
	ft_dprintf(2, "Error: %s\n", s);
	return (-1);
}

static t_ex_ret	connect_according_to_af(char *addr, uint16_t port, int sock)
{
	struct sockaddr_in	sin;
	struct sockaddr_in6	sin6;

	if (g_addr_family == AF_INET6)
	{
		ft_printf("Trying to connect with IPv6 on address %s\n", addr);
		sin6.sin6_family = AF_INET6;
		sin6.sin6_port = htons(port);
		if (inet_pton(AF_INET6, addr, &sin6.sin6_addr) != 1)
			return (print_and_return_failure(INET_PTON_ERR));
		if ((connect(sock, (const struct sockaddr *)&sin6, sizeof(sin6))) == -1)
			return (print_and_return_failure(CONNECT_ERR));
	}
	else
	{
		ft_printf("Trying to connect with IPv4 on address %s\n", addr);
		sin.sin_family = AF_INET;
		sin.sin_port = htons(port);
		if ((sin.sin_addr.s_addr = inet_addr(addr)) == INADDR_NONE)
			return (print_and_return_failure(INET_ADDR_ERR));
		if ((connect(sock, (const struct sockaddr *)&sin, sizeof(sin))) == -1)
			return (print_and_return_failure(CONNECT_ERR));
	}
	return (SUCCESS);
}

static char		*get_real_addr(char *addr)
{
	if (ft_strcmp(addr, "localhost") == 0)
	{
		if (g_addr_family == AF_INET6)
			return (ft_strdup("::1"));
		else
			return (ft_strdup("127.0.0.1"));
	}
	return (ft_strdup(addr));
}

int				connect_to_server(char *addr, uint16_t port)
{
	int					sock;
	struct protoent		*proto;
	char				*real_addr;

	if ((proto = getprotobyname("tcp")) == NULL)
		return (ret_err_neg("During getprotobyname"));
	if ((sock = socket((g_addr_family == AF_INET6 ? PF_INET6 : PF_INET),
			SOCK_STREAM, proto->p_proto)) < 0)
		return (ret_err_neg(SOCKET_ERR));
	real_addr = get_real_addr(addr);
	if (connect_according_to_af(real_addr, port, sock) == FAILURE)
	{
		free(real_addr);
		return (-1);
	}
	free(real_addr);
	return (sock);
}
