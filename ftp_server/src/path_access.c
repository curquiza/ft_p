#include "server.h"

char	*get_root_path(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
		ft_dprintf(2, ROOT_PATH_ERR);
	return (path);
}

static t_bool	path_is_in_server(char *path)
{
	return (ft_strstr(path, g_root_path) == path);
}

static void		check_path_in_child_process(char *path)
{
	char	*tmp_path;
	t_bool	ret;

	chdir(path);
	tmp_path = getcwd(NULL, 0);
	if (tmp_path == NULL)
		exit(1);
	ret = path_is_in_server(ft_strstr(tmp_path, g_root_path));
	free(tmp_path);
	if (ret == TRUE)
		exit(0);
	exit(1);
}

char 			*get_path_in_server(char *path)
{
	pid_t	pid;
	int		status;
	// char	*tmp_path;

	status = 0;
	if ((pid = fork()) < 0)
		return (ft_strdup("."));
	if (pid == 0)
		check_path_in_child_process(path);
	else
		wait4(0, &status, 0, NULL);
	if (status == 0)
	{
		// tmp_path = ft_strstr(path, g_root_path) + ft_strlen(g_root_path);
		return (ft_strdup(path));
	}
	return (ft_strdup("."));
}
