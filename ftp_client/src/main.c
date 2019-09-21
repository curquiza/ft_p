#include "client.h"

static uint16_t	get_port_uint16(char *port_str)
{
	int32_t		port;

	if (ft_is_int(port_str) == FALSE)
	{
		ft_dprintf(2, "ERROR: %s: %s\n", port_str, PORT_ERR);
		return (0);
	}
	port = ft_atoi(port_str);
	if (port < 1 || port > USHRT_MAX)
	{
		ft_dprintf(2, "ERROR: %d: %s\n", port, PORT_ERR);
		return (0);
	}
	return ((uint16_t)port);
}


static t_ex_ret	init(int argc, char **argv, char *addr, uint16_t *port)
{
	int		first_arg_index;

	if (argc < 3)
	{
		usage(argv[0]);
		return (FAILURE);
	}
	g_flags = 0;
	g_run = TRUE;
	if ((first_arg_index = get_all_options(argc, argv)) == -1)
		return (FAILURE);
	if (first_arg_index + 2 != argc)
	{
		usage(argv[0]);
		return (FAILURE);
	}
	g_addr_family = (opt_is_activated('6') == TRUE) ? AF_INET6 : AF_INET;
	signal(SIGINT, sigint_handler);
	ft_bzero(addr, ADDR_MAX_SIZE + 1);
	ft_strncpy(addr, argv[first_arg_index], ADDR_MAX_SIZE);
	*port = get_port_uint16(argv[first_arg_index + 1]);
	if (*port == 0)
		return (FAILURE);
	return (SUCCESS);
}

int		main(int argc, char **argv)
{
	char		addr[ADDR_MAX_SIZE + 1];
	uint16_t	port;

	if (init(argc, argv, addr, &port) == FAILURE)
		return (FAILURE);
	if ((g_sock = connect_to_server(addr, port)) == -1)
		return (FAILURE);
	return (communicate_with_server());
}
