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

static int		create_server_socket_on_valid_port(t_user *user)
{
	int 				sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;
	uint16_t			port;

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
			print_debug_output("Available port found :", user->dt_port, NULL, NULL);
			break;
		}
		port++;
	}
	if (port > PORT_MAX_RANGE)
	{
		print_debug_output(NULL, 0, "No port available to create DT channel", NULL);
		return (-1);
	}
	listen(sock, LISTEN_NB);
	return (sock);
}

void		exec_pasv_cmd(t_user *user, char *cmd)
{
	char				*response;
	unsigned int		dt_size;
	struct sockaddr_in	dt_sin;

	(void)cmd; // check si zero parametre
	if ((user->dt_server_sock = create_server_socket_on_valid_port(user)) == -1)
	{
		send_oneline_reply_to_user(user, RES_425);
		return ;
	}
	print_data_output("Socket server listening on port", user->dt_port,
		NULL, NULL);
	response = get_pasv_response(DEF_SIN_ADDR, user->dt_port);
	send_oneline_reply_to_user(user, response);
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
	free(response);
}
