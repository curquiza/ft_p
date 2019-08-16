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

void		close_user_data_channel(t_user *user)
{
	print_data_output("Closing DT channel on port", user->dt_port, NULL, NULL);
	close(user->dt_client_sock);
	close(user->dt_server_sock);
	user->dt_client_sock = -1;
	user->dt_server_sock = -1;
}
