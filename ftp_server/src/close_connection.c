#include "server.h"

t_ex_ret	close_server(int server_sock)
{
	if (server_sock == -1)
		return (FAILURE);
	ft_putchar('\n');
	print_ctrl_output(NULL, 0, "Closing FTP Server...", NULL);
	free(g_root_path);
	if (close(g_server_sock) == -1)
		return (FAILURE);
	return (SUCCESS);
}

void		close_user_data_channel(t_user *user)
{
	if (user->mode == PASSIVE && user->dt_port != 0)
		print_data_output("Closing DT channel on port", user->dt_port,
			NULL, NULL);
	else if (user->dt_port != 0)
		print_data_output("Closing DT channel with user's port", user->dt_port,
			NULL, NULL);
	if (user->dt_client_sock > 0)
		close(user->dt_client_sock);
	if (user->mode == PASSIVE && user->dt_server_sock > 0)
		close(user->dt_server_sock);
	user->dt_client_sock = -1;
	user->dt_server_sock = -1;
	user->dt_port = 0;
	user->mode = NONE;
}
