/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 14:47:24 by curquiza          #+#    #+#             */
/*   Updated: 2019/11/22 14:47:25 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	quit_cmd(char *input)
{
	if (has_no_arg(input) == FALSE)
	{
		ft_printf("%s\n", ARG_NB_ERR);
		ft_printf("Usage: %s\n", QUIT_USAGE);
		return ;
	}
	g_run = FALSE;
	free(g_client.current_path);
	free(g_client.addr);
	printf("Quitting FTP Client...\n");
	close(g_client.sock);
}
