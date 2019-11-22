/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_stor_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 12:28:28 by curquiza          #+#    #+#             */
/*   Updated: 2019/11/22 12:28:29 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static char		*get_stor_arg(t_user *user, char *cmd)
{
	char	**args;
	int		size;
	char	*rslt;

	args = ft_strsplit(cmd, ' ');
	if (!args)
		ft_exit(MALLOC_ERR, 1);
	size = ft_tablen(args);
	if (size != 2)
	{
		send_oneline_reply_to_user(user, RES_501);
		ft_tabdel(&args);
		return (NULL);
	}
	rslt = get_valid_path_from_user_input(args[1]);
	ft_tabdel(&args);
	if (!rslt)
		send_oneline_reply_to_user(user, RES_550_1);
	return (rslt);
}

static int		get_fd_for_transfer(t_user *user, char *cmd)
{
	char			*path;
	int				fd;

	if ((path = get_stor_arg(user, cmd)) == NULL)
	{
		close_user_data_channel(user);
		return (-1);
	}
	if (is_dt_channel_open(user) == FALSE)
	{
		free(path);
		send_oneline_reply_to_user(user, RES_426);
		close_user_data_channel(user);
		return (-1);
	}
	if ((fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
	{
		free(path);
		send_oneline_reply_to_user(user, RES_451);
		close_user_data_channel(user);
		return (-1);
	}
	send_oneline_reply_to_user(user, RES_125);
	free(path);
	return (fd);
}

static t_ex_ret	write_content_into_new_file(int fd, char *content, int size)
{
	int	size_written;
	int	ret;

	size_written = 0;
	ret = 0;
	while (size_written < size)
	{
		ret = write(fd, content, size - size_written);
		if (ret == -1)
			return (FAILURE);
		size_written += ret;
	}
	return (SUCCESS);
}

void			exec_stor_cmd(t_user *user, char *cmd)
{
	int		fd;
	char	*file_content;
	int		file_size;

	if ((fd = get_fd_for_transfer(user, cmd)) == -1)
		return ;
	if ((file_content = get_file_content(user, &file_size)) == NULL)
	{
		send_oneline_reply_to_user(user, RES_451);
		close_user_data_channel(user);
		return ;
	}
	if (write_content_into_new_file(fd, file_content, file_size) == FAILURE)
		send_oneline_reply_to_user(user, RES_451);
	else
	{
		log_data_received_from_dt_channel(user, "* FILE *");
		send_oneline_reply_to_user(user, RES_226);
	}
	close(fd);
	free(file_content);
	close_user_data_channel(user);
}
