#include "server.h"

static t_ex_ret	init(int argc, char **argv)
{
	if (argc < 2)
	{
		usage(argv[0]);
		return (FAILURE);
	}
	g_server_sock = -1;
	g_flags = 0;
	g_root_path = NULL;
	signal(SIGINT, sigint_handler);
	return (SUCCESS);
}

static int	get_port_index(int argc, char **argv)
{
	int			port_index;

	if ((port_index = get_all_options(argc, argv)) == -1)
		return (-1);
	if ((port_index + 1) != argc)
	{
		usage(argv[0]);
		return (-1);
	}
	return (port_index);
}

static uint16_t		get_port_uint16(char *port_str)
{
	int32_t		port;

	if (ft_is_int(port_str) == FALSE)
	{
		ft_dprintf(2, "Error: %s: %s\n", port_str, PORT_ERR);
		return (0);
	}
	port = ft_atoi(port_str);
	if (port < PORT_MIN_RANGE || port > USHRT_MAX)
	{
		ft_dprintf(2, "Error: %d: %s\n", port, PORT_ERR);
		return (0);
	}
	return ((uint16_t)port);
}

static int		ret_err_neg(char *s)
{
	ft_dprintf(2, "Error: %s\n", s);
	return (-1);
}

static int		create_server_socket(uint16_t port)
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


static char	*get_root_path(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
		ft_dprintf(2, ROOT_PATH_ERR);
	return (path);
}

int					main(int argc, char **argv)
{
	uint16_t	port;
	int			port_index;

	if (init(argc, argv) == FAILURE)
		return (FAILURE);
	if ((port_index = get_port_index(argc, argv)) == -1)
		return (FAILURE);
	if ((port = get_port_uint16(argv[port_index])) == 0)
		return (FAILURE);
	if ((g_server_sock = create_server_socket(port)) == -1)
		return (FAILURE);
	if ((g_root_path = get_root_path()) == NULL)
		return (FAILURE);
	print_ctrl_output("Opening FTP Server on port", port, NULL, NULL);
	return (listen_to_clients(g_server_sock));
}
