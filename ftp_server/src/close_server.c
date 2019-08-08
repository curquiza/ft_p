#include "server.h"

t_ex_ret	close_server(int server_sock)
{
	if (server_sock == -1)
		return (FAILURE);
	ft_printf("\nClosing FTP Server...\n");
	if (close(g_server_sock) == -1)
		return (FAILURE);
	return (SUCCESS);
}
