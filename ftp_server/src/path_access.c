/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_access.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 12:29:00 by curquiza          #+#    #+#             */
/*   Updated: 2019/11/22 12:29:01 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static t_bool	path_is_in_server_folder(char *path)
{
	return (ft_strstr(path, g_root_path) == path);
}

/*
** Retry needed because user can ask for "ls <filename>"
** and not only "ls <foldername>"
*/

static void		retry_chdir_with_new_path(char *path)
{
	int		len;
	char	*new_path;
	char	*tmp_path;
	int		index;

	len = ft_strlen(path);
	new_path = ft_strdup(path);
	if (len > 0 && new_path[len - 1] == '/')
		new_path[len - 1] = '\0';
	tmp_path = ft_strrchr(new_path, '/');
	if (tmp_path == NULL)
	{
		free(new_path);
		return ;
	}
	index = tmp_path - new_path;
	new_path[index] = '\0';
	chdir(new_path);
	free(new_path);
}

static void		check_path_in_child_process(char *path)
{
	char	*tmp_path;
	t_bool	ret;

	if (chdir(path) != 0)
		retry_chdir_with_new_path(path);
	tmp_path = getcwd(NULL, 0);
	if (tmp_path == NULL)
		exit(1);
	ret = path_is_in_server_folder(tmp_path);
	free(tmp_path);
	if (ret == TRUE)
		exit(0);
	exit(1);
}

char			*get_valid_path_from_user_input(char *path)
{
	char	*new_path;
	pid_t	pid;
	int		status;

	if (path[0] == '/')
		new_path = ft_strjoin(g_root_path, path);
	else
		new_path = ft_strdup(path);
	status = 0;
	if ((pid = fork()) < 0)
		return (NULL);
	if (pid == 0)
		check_path_in_child_process(new_path);
	else
		wait4(0, &status, 0, NULL);
	if (WIFEXITED(status) == TRUE && WEXITSTATUS(status) == 0)
		return (new_path);
	return (NULL);
}

char			*get_current_wd_in_server(void)
{
	char	*current_path;
	char	*new_path;

	current_path = getcwd(NULL, 0);
	if (!current_path || path_is_in_server_folder(current_path) == FALSE)
	{
		free(current_path);
		return (NULL);
	}
	if (*(current_path + ft_strlen(g_root_path)) == 0)
		new_path = ft_strjoin("/", current_path + ft_strlen(g_root_path));
	else
		new_path = ft_strdup(current_path + ft_strlen(g_root_path));
	return (new_path);
}
