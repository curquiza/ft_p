/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_connection_active.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 14:46:17 by curquiza          #+#    #+#             */
/*   Updated: 2019/11/22 14:46:18 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void	send_request_connection_to_server(uint16_t dt_port)
{
	char		*response;
	char		*tmp_int;
	char		*tmp_res;

	if (g_client.addr_family == AF_INET6)
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

	if (g_client.addr_family == AF_INET6)
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

t_ex_ret	etablish_data_connection_active(t_dt_socks *dt)
{
	uint16_t	dt_port;
	char		reply_buff[REPLY_MAX_SIZE];

	dt->server_sock = create_server_socket_on_valid_port(&dt_port);
	if (dt->server_sock == -1)
		return (print_and_return_failure(DATA_CONN_ERR));
	send_request_connection_to_server(dt_port);
	if (parse_and_display_reply(reply_buff) != 0)
		return (print_and_return_failure(DATA_CONN_ERR));
	if ((dt->client_sock = accept_according_to_af(dt->server_sock)) == -1)
		return (print_and_return_failure(DATA_CONN_ERR));
	return (SUCCESS);
}
