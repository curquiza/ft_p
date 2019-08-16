#include "server.h"

static char		*get_pasv_response(int addr, uint16_t port)
{
	char		*s;
	t_byte		p1;
	t_byte		p2;

	(void)addr;
	p2 = (t_byte)(port & 0x00ff);
	p1 = (t_byte)((port >> 8) & 0x00ff);
	asprintf(&s, "227 Entering Passive Mode (0,0,0,0,%hhu,%hhu)", p1, p2); // !!!

	return (s);
}

void		exec_pasv_cmd(t_user *user, char *cmd)
{
	uint16_t			port;
	char				*response;
	unsigned int		dt_size;
	struct sockaddr_in	dt_sin;

	(void)cmd;
	user->dt_server_sock = create_server_socket_on_random_port(&port);
	if (user->dt_server_sock == -1)
		return ; // send error reply to user
	user->dt_port = port;
	print_data_output("Socket server listening on port", user->dt_port, NULL, NULL);
	response = get_pasv_response(DEF_SIN_ADDR, port);
	send_oneline_reply_to_user(user->ctrl_client_sock, user->num, response);

	user->dt_client_sock = accept(user->dt_server_sock, (struct sockaddr *)&dt_sin, &dt_size);
	if (user->dt_client_sock < 0)
		return ; // send error reply to user
	print_data_output("Connection accepted on port", user->dt_port, ": DT channel created", NULL);
	free(response);
}
