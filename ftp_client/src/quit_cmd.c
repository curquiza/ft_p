#include "client.h"

void	quit_cmd(char *input)
{
	if (has_no_arg(input) == FALSE)
	{
		ft_dprintf(2, "%s\n", ARG_NB_ERR);
		ft_dprintf(2, "Usage: quit\n");
		return ;
	}
	g_run = FALSE;
	printf("Quitting FTP Client...\n");
	close(g_sock);
}
