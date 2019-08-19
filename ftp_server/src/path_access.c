#include "server.h"

char	*get_root_path(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
		ft_dprintf(2, ROOT_PATH_ERR);
	return (path);
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

char 			*get_path_for_list_cmd(char *path)
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
		return (ft_strdup("."));
	if (pid == 0)
		check_path_in_child_process(new_path);
	else
		wait4(0, &status, 0, NULL);
	if (status == 0)
		return (new_path);
	return (NULL);
}
