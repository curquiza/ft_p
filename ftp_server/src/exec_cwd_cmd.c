#include "server.h"

static t_bool	is_dir(char *path)
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
	if (S_ISDIR(buff.st_mode) == TRUE)
		ret = TRUE;
	close(fd);
	return (ret);
}

static char		*get_cwd_arg(t_user *user, char *cmd)
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
	rslt = get_valid_path_for_cmd(args[1]);
	ft_tabdel(&args);
	if (!rslt)
		send_oneline_reply_to_user(user, RES_550_1);
	else if (is_dir(rslt) == FALSE)
		send_oneline_reply_to_user(user, RES_550_3);
	return (rslt);
}

void			exec_cwd_cmd(t_user *user, char *cmd)
{
	char	*path;
	char	*res;

	if ((path = get_cwd_arg(user, cmd)) == NULL)
		return ;
	if (chdir(path) != 0)
		send_oneline_reply_to_user(user, RES_451);
	else
	{
		free(path);
		path = get_current_wd_in_server();
		if (!path)
		{
			send_oneline_reply_to_user(user, RES_550_1);
			free(path);
			return ;
		}
		res = ft_strjoin("200 directory changed to ", path);
		send_oneline_reply_to_user(user, res);
		free(res);
	}
	free(path);
}
