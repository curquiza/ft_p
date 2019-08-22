#include "server.h"

void	send_oneline_reply_to_user(t_user *user, char *str)
{
	char	*cmd;
	size_t	str_len;

	if (str == NULL)
		return ;
	str_len = ft_strlen(str);
	if ((cmd = ft_memalloc(str_len + 2)) == NULL)
		ft_exit(MALLOC_ERR, FAILURE);
	ft_memmove(cmd, str, str_len);
	cmd[str_len] = '\r';
	cmd[str_len + 1] = '\n';
	send(user->ctrl_client_sock, cmd, str_len + 2, 0);
	print_ctrl_output("--> Sent to Client", user->num, ":", str);
	free(cmd);
}
