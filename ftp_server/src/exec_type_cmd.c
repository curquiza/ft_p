#include "server.h"

void	exec_type_cmd(t_user *user, char *cmd)
{
	(void)cmd;
	send_oneline_reply_to_user(user, "200 New type set.");
}
