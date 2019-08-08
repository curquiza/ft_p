#include "server.h"

void	usage(char *prgm)
{
	ft_dprintf(2, "Usage: %s: ./server [-v] <port>\n", prgm);
	ft_dprintf(2, "  -v : verbose mode\n");
}
