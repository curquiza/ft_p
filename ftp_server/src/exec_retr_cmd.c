/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_retr_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 12:28:21 by curquiza          #+#    #+#             */
/*   Updated: 2019/11/22 12:28:22 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static t_bool	is_regfile(char *path)
{
	int			fd;
	struct stat	buff;
	t_bool		ret;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (FALSE);
	if (fstat(fd, &buff) == -1)
		return (FALSE);
	ret = FALSE;
	if (S_ISREG(buff.st_mode) == TRUE)
		ret = TRUE;
	close(fd);
	return (ret);
}

static char		*get_retr_arg(t_user *user, char *cmd)
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
	else if (is_regfile(rslt) == FALSE)
	{
		free(rslt);
		send_oneline_reply_to_user(user, RES_550_2);
		return (NULL);
	}
	return (rslt);
}

static int		get_fd_for_transfer(t_user *user, char *cmd)
{
	char			*path;
	int				fd;

	if ((path = get_retr_arg(user, cmd)) == NULL)
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
	if ((fd = open(path, O_RDONLY)) == -1)
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

static int		get_file_size(t_user *user, int fd)
{
	struct stat		stat_struct;

	if (fstat(fd, &stat_struct) == -1)
	{
		send_oneline_reply_to_user(user, RES_451);
		close_user_data_channel(user);
		return (-1);
	}
	return (stat_struct.st_size);
}

void			exec_retr_cmd(t_user *user, char *cmd)
{
	int				size;
	t_byte			*ptr;
	int				fd;

	if ((fd = get_fd_for_transfer(user, cmd)) == -1)
		return ;
	if ((size = get_file_size(user, fd)) == -1)
	{
		close(fd);
		return ;
	}
	if ((ptr = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0)) == NULL)
	{
		send_oneline_reply_to_user(user, RES_451);
		close_user_data_channel(user);
		close(fd);
		return ;
	}
	send_file(user, ptr, size);
	close_user_data_channel(user);
	close(fd);
}
