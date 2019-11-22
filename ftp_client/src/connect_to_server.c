/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_to_server.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 14:46:14 by curquiza          #+#    #+#             */
/*   Updated: 2019/11/22 14:46:15 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static t_ex_ret	connect_according_to_af(char *addr, uint16_t port, int sock)
{
	struct sockaddr_in	sin;
	struct sockaddr_in6	sin6;

	if (g_client.addr_family == AF_INET6)
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

int				connect_to_server(char *addr, uint16_t port)
{
	int					sock;
	struct protoent		*proto;

	if ((proto = getprotobyname(TCP_PROTONAME)) == NULL)
		return (print_and_return_neg(PROTOBYNAME_ERR));
	if ((sock = socket((g_client.addr_family == AF_INET6 ? PF_INET6 : PF_INET),
			SOCK_STREAM, proto->p_proto)) < 0)
		return (print_and_return_neg(SOCKET_ERR));
	if (connect_according_to_af(addr, port, sock) == FAILURE)
		return (-1);
	return (sock);
}
