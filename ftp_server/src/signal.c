#include "server.h"

void	sigint_handler(int sig)
{
	(void)sig;
	exit(close_server(g_server_sock));
}

void	child_signals_handler(void)
{
	signal(SIGINT, SIG_DFL);
}
