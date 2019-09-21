#include "client.h"

void	quit_cmd(char *input)
{
	(void)input;
	g_run = FALSE;
	printf("Quitting FTP Client...\n");
	close(g_sock);
}
