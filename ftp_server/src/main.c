#include "server.h"

static t_ex_ret	init(int argc, char **argv)
{
	if (argc != 2)
	{
		usage(argv[0]);
		return (FAILURE);
	}
	g_server_sock = -1;
	signal(SIGINT, sigint_handler);
	return (SUCCESS);
}


static uint16_t		get_port(char *port_str)
{
	int32_t		port;

	if (ft_is_int(port_str) == FALSE)
	{
		ft_dprintf(2, "Error: %s: %s\n", port_str, PORT_ERR);
		return (0);
	}
	port = ft_atoi(port_str);
	if (port <= 0 || port > USHRT_MAX)
	{
		ft_dprintf(2, "Error: %d: %s\n", port, PORT_ERR);
		return (0);
	}
	return ((uint16_t)port);
}

int					main(int argc, char **argv)
{
	uint16_t	port;

	if (init(argc, argv) == FAILURE)
		return (FAILURE);
	if ((port = get_port(argv[1])) == 0)
		return (FAILURE);

	if ((g_server_sock = create_server(port)) == -1)
		return (FAILURE);

	printf("FTP Server open on port %d\n", port);
	listen_to_clients(g_server_sock);

	return (SUCCESS);
}
