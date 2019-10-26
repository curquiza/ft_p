#include "client.h"

t_ex_ret		bind_server(int sock, uint16_t port)
{
	struct sockaddr_in	sin;
	struct sockaddr_in6	sin6;

	if (g_addr_family == AF_INET6)
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


static t_ex_ret		get_user_dt_port(uint16_t *dt_port, int sock)
{
	uint16_t			port;

	port = PORT_MIN_RANGE;
	while (port <= PORT_MAX_RANGE)
	{
		// print_debug_output("Testing port", port, "for DT channel...", NULL);
		if (bind_server(sock, port) == SUCCESS)
		{
			*dt_port = port;
			// print_debug_output("Available port found :", port, NULL, NULL);
			return (SUCCESS);
		}
		port++;
	}
	return (FAILURE);
}


static int	socket_according_to_af(void)
{
	int					sock;
	struct protoent		*proto;

	sock = -1;
	if ((proto = getprotobyname(TCP_PROTONAME)) == NULL)
		return (print_and_return_neg(PROTOBYNAME_ERR));
	if (g_addr_family == AF_INET6)
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

static int		create_server_socket_on_valid_port(uint16_t *dt_port)
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

static void	send_request_connection_to_server(uint16_t dt_port)
{
	char		*response;
	char		*tmp_int;
	char		*tmp_res;

	if (g_addr_family == AF_INET6)
	{
		tmp_int = ft_itoa(dt_port);
		response = ft_strjoin3("EPRT |2|::|",
			tmp_int, "|");
		free(tmp_int);
	}
	else
	{
		tmp_int = ft_itoa((int)((t_byte)((dt_port >> 8) & 0x00ff)));
		response = ft_strjoin3("PORT 0,0,0,0,", tmp_int, ",");
		free(tmp_int);
		tmp_int = ft_itoa((int)((t_byte)(dt_port & 0x00ff)));
		tmp_res = response;
		response = ft_strjoin(response, tmp_int);
		free(tmp_res);
		free(tmp_int);
	}
	send_to_server(response);
	free(response);
}

static int	accept_according_to_af(int dt_server_sock)
{
	unsigned int		dt_size;
	struct sockaddr_in	dt_sin;
	struct sockaddr_in6	dt_sin6;
	int					dt_client_sock;

	if (g_addr_family == AF_INET6)
	{
		if ((dt_client_sock = accept(dt_server_sock,
			(struct sockaddr *)&dt_sin6, &dt_size)) < 0)
			return (-1);
	}
	else
	{
		if ((dt_client_sock = accept(dt_server_sock,
			(struct sockaddr *)&dt_sin, &dt_size)) < 0)
			return (-1);
	}
	return (dt_client_sock);
}

int		etablish_data_connection_active(void)
{
	int			dt_server_sock;
	uint16_t	dt_port;
	int			dt_client_sock;

	dt_server_sock = create_server_socket_on_valid_port(&dt_port);
	if (dt_server_sock == -1)
		return (print_and_return_neg(DATA_CONN_ERR));
	send_request_connection_to_server(dt_port);
	if ((dt_client_sock = accept_according_to_af(dt_server_sock)) == -1)
		return (print_and_return_neg(DATA_CONN_ERR));
	return (dt_client_sock);
}
