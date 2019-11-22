/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 12:28:18 by curquiza          #+#    #+#             */
/*   Updated: 2019/11/22 12:28:19 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	exec_pwd_cmd(t_user *user, char *cmd)
{
	char	*tmp_res;
	char	*current_wd;

	if (cmd_has_no_arg(user, cmd) == FALSE)
		return ;
	current_wd = get_current_wd_in_server();
	if (!current_wd)
	{
		send_oneline_reply_to_user(user, RES_550_1);
		free(current_wd);
		return ;
	}
	tmp_res = ft_strjoin3("257 \"", current_wd, "\" is the current directory.");
	send_oneline_reply_to_user(user, tmp_res);
	free(tmp_res);
	free(current_wd);
}
