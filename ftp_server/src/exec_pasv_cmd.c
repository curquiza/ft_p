#include "server.h"

static void		send_pasv_response(t_user *user, int addr)
{
	char		*response;
	t_byte		p1;
	t_byte		p2;

	(void)addr;
	p2 = (t_byte)(user->dt_port & 0x00ff);
	p1 = (t_byte)((user->dt_port >> 8) & 0x00ff);
	asprintf(&response, "227 Entering Passive Mode (0,0,0,0,%hhu,%hhu)", p1, p2); // !!!
	send_oneline_reply_to_user(user, response);
	free(response);
}

static t_ex_ret		get_user_dt_port(t_user *user, int sock)
{
	struct sockaddr_in	sin;
	uint16_t			port;

	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = htonl(DEF_SIN_ADDR);
	port = PORT_MIN_RANGE;
	while (port <= PORT_MAX_RANGE)
	{
		sin.sin_port = htons(port);
		print_debug_output("Testing port", port, "for DT channel...", NULL);
		if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) != -1)
		{
			user->dt_port = port;
			print_debug_output("Available port found :", port, NULL, NULL);
			return (SUCCESS);
		}
		port++;
	}
	return (FAILURE);
}

static int		create_server_socket_on_valid_port(t_user *user)
{
	int 				sock;
	struct protoent		*proto;

	if ((proto = getprotobyname("tcp")) == NULL)
	{
		print_debug_output(NULL, 0, "Error during getprotobyname", NULL);
		return (-1);
	}
	if ((sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)) == -1)
	{
		print_debug_output(NULL, 0, "Error during socket server creation", NULL);
		return (-1);
	}
	if (get_user_dt_port(user, sock) == FAILURE)
	{
		print_debug_output(NULL, 0, "No port available to create DT channel",
			NULL);
		return (-1);
	}
	listen(sock, LISTEN_NB);
	return (sock);
}

void		exec_pasv_cmd(t_user *user, char *cmd)
{
	unsigned int		dt_size;
	struct sockaddr_in	dt_sin;

	if (cmd_has_no_arg(user, cmd) == FALSE)
		return ;
	if ((user->dt_server_sock = create_server_socket_on_valid_port(user)) == -1)
	{
		send_oneline_reply_to_user(user, RES_425);
		return ;
	}
	print_data_output("Socket server listening on port", user->dt_port,
		NULL, NULL);
	send_pasv_response(user, DEF_SIN_ADDR);
	if ((user->dt_client_sock
	= accept(user->dt_server_sock, (struct sockaddr *)&dt_sin, &dt_size)) < 0)
	{
		print_debug_output(NULL, 0, "Error during accept", NULL);
		send_oneline_reply_to_user(user, RES_425);
		return ;
	}
	print_data_output("Connection accepted on port", user->dt_port,
		": DT channel created [PASSIVE MODE]", NULL);
	user->mode = PASSIVE;
}
