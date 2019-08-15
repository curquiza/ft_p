#include "server.h"

t_ex_ret	close_server(int server_sock)
{
	if (server_sock == -1)
		return (FAILURE);
	print_ctrl_output(NULL, 0, "\nClosing FTP Server...", NULL);
	if (close(g_server_sock) == -1)
		return (FAILURE);
	return (SUCCESS);
}
