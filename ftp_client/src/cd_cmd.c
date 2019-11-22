/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 14:46:07 by curquiza          #+#    #+#             */
/*   Updated: 2019/11/22 14:46:08 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void	send_cwd_cmd_to_server(char *input)
{
	char	**args;
	char	*cmd;

	args = ft_strsplit(input, ' ');
	cmd = ft_strjoin("CWD ", args[1]);
	send_to_server(cmd);
	ft_tabdel(&args);
	free(cmd);
}

void		cd_cmd(char *input)
{
	char	reply_buff[REPLY_MAX_SIZE];

	if (has_only_one_arg(input) == FALSE)
	{
		ft_printf("%s\n", ARG_NB_ERR);
		ft_printf("Usage: %s\n", CD_USAGE);
		return ;
	}
	send_cwd_cmd_to_server(input);
	if (parse_and_display_reply(reply_buff) == 0)
		pwd_cmd("pwd");
}
