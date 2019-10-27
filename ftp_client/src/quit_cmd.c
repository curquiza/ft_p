#include "client.h"

void	quit_cmd(char *input)
{
	if (has_no_arg(input) == FALSE)
	{
		ft_printf("%s\n", ARG_NB_ERR);
		ft_printf("Usage: %s\n", QUIT_USAGE);
		return ;
	}
	g_run = FALSE;
	free(g_client.current_path);
	free(g_client.addr);
	printf("Quitting FTP Client...\n");
	close(g_client.sock);
}
