#include "server.h"

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
	// return RES_550_3 si le path est un fichier
	if (!rslt)
		send_oneline_reply_to_user(user, RES_550_1);
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
		// mettre un pimpé pour la réponse en faisant un cwd.
		// utiliser la fonction dans pwd
		res = ft_strjoin("200 directory changed to ", path);
		send_oneline_reply_to_user(user, res);
		free(res);
	}
	free(path);
}
