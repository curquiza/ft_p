/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_main_server_socket.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 12:27:32 by curquiza          #+#    #+#             */
/*   Updated: 2019/11/22 12:27:33 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		create_main_server_socket(uint16_t port)
{
	int					sock;
	struct protoent		*proto;

	if ((proto = getprotobyname(TCP_PROTONAME)) == NULL)
		return (ret_err_neg(PROTOBYNAME_ERR));
	if (opt_is_activated('6') == TRUE)
	{
		g_addr_family = AF_INET6;
		print_debug_output(NULL, 0, "IPv6 Protocol", NULL);
		if ((sock = socket(PF_INET6, SOCK_STREAM, proto->p_proto)) == -1)
			return (ret_err_neg(SOCKET_ERR));
	}
	else
	{
		print_debug_output(NULL, 0, "IPv4 Protocol", NULL);
		g_addr_family = AF_INET;
		if ((sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)) == -1)
			return (ret_err_neg(SOCKET_ERR));
	}
	if (bind_server(sock, port) == FAILURE)
		return (ret_err_neg(BIND_ERR));
	if (listen(sock, LISTEN_NB) == -1)
		return (ret_err_neg(LISTEN_ERR));
	return (sock);
}
