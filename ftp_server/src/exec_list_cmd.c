/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 12:28:05 by curquiza          #+#    #+#             */
/*   Updated: 2019/11/22 12:28:06 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static char	*get_ls_arg(t_user *user, char *cmd)
{
	char	**args;
	int		size;
	char	*rslt;

	args = ft_strsplit(cmd, ' ');
	if (!args)
		ft_exit(MALLOC_ERR, 1);
	size = ft_tablen(args);
	if (size > 2 || (size == 2 && args[1][0] == '-'))
	{
		send_oneline_reply_to_user(user, RES_501);
		ft_tabdel(&args);
		return (NULL);
	}
	rslt = NULL;
	if (size == 1)
		rslt = ft_strdup(".");
	else if (size == 2)
		rslt = get_valid_path_from_user_input(args[1]);
	ft_tabdel(&args);
	if (rslt == NULL)
		send_oneline_reply_to_user(user, RES_550_2);
	return (rslt);
}

static void	child_process(t_user *user, char *ls_arg)
{
	char	*args[4];

	args[0] = "/bin/ls";
	args[1] = "-la";
	args[2] = ls_arg;
	args[3] = NULL;
	send_oneline_reply_to_user(user, RES_125);
	if (dup2(user->dt_client_sock, STDOUT_FILENO) == -1
		|| dup2(user->dt_client_sock, STDERR_FILENO) == -1)
		exit(-1);
	execv(args[0], args);
	free(ls_arg);
	exit(-1);
}

/*
**	255 => -1
*/

static void	parent_process(t_user *user)
{
	int		status;

	status = 0;
	wait4(0, &status, 0, NULL);
	if ((WIFEXITED(status) == TRUE && WEXITSTATUS(status) == 255)
		|| (WIFEXITED(status) == FALSE))
	{
		print_data_output(NULL, 0, LS_ERR, NULL);
		send_oneline_reply_to_user(user, RES_451);
		close_user_data_channel(user);
		return ;
	}
	log_data_sent_into_dt_channel(user, "* LS OUTPUT *");
	close_user_data_channel(user);
	send_oneline_reply_to_user(user, RES_226);
}

void		exec_list_cmd(t_user *user, char *cmd)
{
	char	*ls_arg;
	pid_t	pid;

	if (!(ls_arg = get_ls_arg(user, cmd)))
		return (close_user_data_channel(user));
	if (is_dt_channel_open(user) == FALSE)
	{
		free(ls_arg);
		send_oneline_reply_to_user(user, RES_426);
		return (close_user_data_channel(user));
	}
	if ((pid = fork()) < 0)
	{
		free(ls_arg);
		send_oneline_reply_to_user(user, RES_451);
		return ;
	}
	if (pid == 0)
		child_process(user, ls_arg);
	else
		parent_process(user);
	free(ls_arg);
}
