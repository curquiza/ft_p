#include "server.h"

void		exec_pwd_cmd(t_user *user, char *cmd)
{
	char	*tmp_res;

	(void)cmd;
	tmp_res = ft_strjoin3("257 \"", "path", "\" is the current directory.");
	send_oneline_reply_to_user(user, tmp_res);
	free(tmp_res);
}
