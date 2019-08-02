#include "server.h"

void	sigint_handler(int sig)
{
	(void)sig;
	if (g_server_sock == -1)
		exit(FAILURE);
	printf("\nClosing FTP server...\n");
	if (close(g_server_sock) == -1)
		exit(FAILURE);
	exit(SUCCESS);
}

void	child_signals_handler(void)
{
	signal(SIGINT, SIG_DFL);
}
