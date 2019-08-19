#include "server.h"

void	usage(char *prgm)
{
	ft_dprintf(2, "Usage: %s: ./server [-d] <port>\n", prgm);
	ft_dprintf(2, "  -d : debug mode\n");
}

t_bool	is_dt_channel_open(t_user *user)
{
	if (user->dt_client_sock == -1)
		return (FALSE);
	return (TRUE);
}
