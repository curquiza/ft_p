#include "client.h"

void	usage(char *prgm)
{
	ft_dprintf(2, "Usage: %s: ./client [-6] <address> <port>\n", prgm);
	ft_dprintf(2, "  -6 : IPv6\n");
}
