/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 12:25:50 by curquiza          #+#    #+#             */
/*   Updated: 2019/11/22 12:25:52 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_ex_ret	bind_server(int sock, uint16_t port)
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
