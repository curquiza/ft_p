#include "server.h"

void			exec_pwd_cmd(t_user *user, char *cmd)
{
	char	*tmp_res;
	char	*current_path;
	char	*new_path;

	if (cmd_has_no_arg(user, cmd) == FALSE)
		return ;
	current_path = getcwd(NULL, 0);
	if (!current_path || path_is_in_server_folder(current_path) == FALSE)
	{
		send_oneline_reply_to_user(user, RES_550_1);
		free(current_path);
		return ;
	}
	if (*(current_path + ft_strlen(g_root_path)) == 0)
		new_path = ft_strjoin("/", current_path + ft_strlen(g_root_path));
	else
		new_path = ft_strdup(current_path + ft_strlen(g_root_path));
	tmp_res = ft_strjoin3("257 \"", new_path, "\" is the current directory.");
	send_oneline_reply_to_user(user, tmp_res);
	free(tmp_res);
	free(current_path);
	free(new_path);
}
