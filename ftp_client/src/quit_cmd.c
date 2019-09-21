#include "client.h"

void	quit_cmd(char *input)
{
	(void)input;
	printf("Quitting FTP Client...\n");
	close(g_sock);
}
