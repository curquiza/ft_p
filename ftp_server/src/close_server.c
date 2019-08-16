#include "server.h"

t_ex_ret	close_server(int server_sock)
{
	if (server_sock == -1)
		return (FAILURE);
	ft_putchar('\n');
	print_ctrl_output(NULL, 0, "Closing FTP Server...", NULL);
	if (close(g_server_sock) == -1)
		return (FAILURE);
	return (SUCCESS);
}
