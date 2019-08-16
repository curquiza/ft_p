#include "server.h"

static int		ret_err_neg(char *s)
{
	ft_dprintf(2, "Error: %s\n", s);
	return (-1);
}

int		create_server_socket(uint16_t port)
{
	int 				sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;			// /usr/include/netinet/in.h

	if ((proto = getprotobyname("tcp")) == NULL)
		return (ret_err_neg("During getprotobyname"));
	if ((sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)) == -1)
		return (ret_err_neg("During socket server creation"));
	sin.sin_family = AF_INET; // adress family internet
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(DEF_SIN_ADDR);
	if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
		return (ret_err_neg("During binding"));
	listen(sock, LISTEN_NB);
	return (sock);
}

int		create_server_socket_on_random_port(uint16_t *assigned_port)
{
	int 				sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;
	uint16_t			port;

	if ((proto = getprotobyname("tcp")) == NULL)
		return (ret_err_neg("During getprotobyname"));
	if ((sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)) == -1)
		return (ret_err_neg("During socket server creation"));
	sin.sin_family = AF_INET; // adress family internet
	sin.sin_addr.s_addr = htonl(DEF_SIN_ADDR);

	port = PORT_MIN_RANGE;
	while (port <= PORT_MAX_RANGE)
	{
		sin.sin_port = htons(port);
		print_debug_output("Testing port", port, "for DT channel...", NULL);
		if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) != -1)
		{
			*assigned_port = port;
			print_debug_output("Available port found", *assigned_port, NULL, NULL);
			break;
		}
		port++;
	}
	if (port > PORT_MAX_RANGE)
		return (ret_err_neg("No port available to create data channel"));
	listen(sock, LISTEN_NB);
	return (sock);
}
