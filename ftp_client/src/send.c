/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 14:47:34 by curquiza          #+#    #+#             */
/*   Updated: 2019/11/22 14:47:35 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	send_to_server(char *str)
{
	char	*cmd;
	size_t	str_len;

	if (str == NULL)
		return ;
	str_len = ft_strlen(str);
	if ((cmd = ft_memalloc(str_len + 2)) == NULL)
		ft_exit(MALLOC_ERR, FAILURE);
	ft_memmove(cmd, str, str_len);
	cmd[str_len] = '\r';
	cmd[str_len + 1] = '\n';
	send(g_client.sock, cmd, str_len + 2, 0);
	ft_printf("--> Sent to server : %s\n", str);
	free(cmd);
}
