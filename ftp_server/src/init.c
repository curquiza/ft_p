#include "server.h"

t_ex_ret	init(int argc, char **argv)
{
	if (argc != 2)
	{
		usage(argv[0]);
		return (FAILURE);
	}
	g_server_sock = -1;
	signal(SIGINT, sigint_handler);
	return (SUCCESS);
}
