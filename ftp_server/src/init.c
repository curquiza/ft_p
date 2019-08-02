#include "server.h"

void	init(void)
{
	g_server_sock = -1;
	signal(SIGINT, sigint_handler);
}
