/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etablish_data_connection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 14:46:33 by curquiza          #+#    #+#             */
/*   Updated: 2019/11/22 14:46:33 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void		close_data_connection(t_dt_socks *dt)
{
	if (dt->server_sock > -1)
		close(dt->server_sock);
	if (dt->client_sock > -1)
		close(dt->client_sock);
}

t_ex_ret	etablish_data_connection(t_dt_socks *dt)
{
	dt->client_sock = -1;
	dt->server_sock = -1;
	if (g_client.mode == PASSIVE)
		return (etablish_data_connection_passive(dt));
	return (etablish_data_connection_active(dt));
}
