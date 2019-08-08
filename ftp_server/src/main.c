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
	int			port_index;

	if (init(argc, argv) == FAILURE)
		return (FAILURE);
	if ((port_index = get_port_index(argc, argv)) == -1)
		return (FAILURE);
	if ((port = get_port_uint16(argv[port_index])) == 0)
		return (FAILURE);
	if ((g_server_sock = create_server(port)) == -1)
		return (FAILURE);
	printf("Opening FTP Server on port %d\n", port);
	listen_to_clients(g_server_sock);
	return (SUCCESS);
}
