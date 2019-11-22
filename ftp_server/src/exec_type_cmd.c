/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_type_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 12:28:32 by curquiza          #+#    #+#             */
/*   Updated: 2019/11/22 12:28:34 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	exec_type_cmd(t_user *user, char *cmd)
{
	(void)cmd;
	send_oneline_reply_to_user(user, "200 New type set.");
}
