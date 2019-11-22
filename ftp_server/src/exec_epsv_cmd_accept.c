/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_epsv_cmd_accept.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 12:28:02 by curquiza          #+#    #+#             */
/*   Updated: 2019/11/22 12:28:03 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_ex_ret	accept_according_to_af(t_user *user)
{
	unsigned int		dt_size;
	struct sockaddr_in	dt_sin;
	struct sockaddr_in6	dt_sin6;

	if (g_addr_family == AF_INET6)
	{
		if ((user->dt_client_sock = accept(user->dt_server_sock,
			(struct sockaddr *)&dt_sin6, &dt_size)) < 0)
			return (FAILURE);
	}
	else
	{
		if ((user->dt_client_sock = accept(user->dt_server_sock,
			(struct sockaddr *)&dt_sin, &dt_size)) < 0)
			return (FAILURE);
	}
	return (SUCCESS);
}
