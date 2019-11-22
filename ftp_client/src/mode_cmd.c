/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 14:47:04 by curquiza          #+#    #+#             */
/*   Updated: 2019/11/22 14:47:08 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	mode_cmd(char *input)
{
	if (has_no_arg(input) == FALSE)
	{
		ft_printf("%s\n", ARG_NB_ERR);
		ft_printf("Usage: %s\n", MODE_USAGE);
		return ;
	}
	ft_printf("Current mode: %s\n",
		(g_client.mode == ACTIVE ? "ACTIVE" : "PASSIVE"));
}
