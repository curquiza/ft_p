#include "server.h"

void	usage(char *prgm)
{
	ft_dprintf(2, "Usage: %s: ./server [-d] <port>\n", prgm);
	ft_dprintf(2, "  -d : debug mode\n");
}
