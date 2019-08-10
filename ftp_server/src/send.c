#include "server.h"

void	send_oneline_reply_to_user(int client_sock, int client_num, char *str)
{
	char	*cmd;
	size_t	str_len;

	str_len = ft_strlen(str);
	if ((cmd = ft_memalloc(str_len + 2)) == NULL)
		ft_exit(MALLOC_ERR, FAILURE);
	ft_memmove(cmd, str, str_len);
	cmd[str_len] = '\r';
	cmd[str_len + 1] = '\n';
	send(client_sock, cmd, str_len + 2, 0);
	print_verbose_siss("Sent to Client", client_num, ":", str);
	free(cmd);
}
