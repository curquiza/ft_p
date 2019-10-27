#include "client.h"

static uint16_t	get_port_uint16(char *port_str)
{
	int32_t		port;

	if (ft_is_int(port_str) == FALSE)
	{
		ft_printf("ERROR: %s: %s\n", port_str, PORT_ERR);
		return (0);
	}
	port = ft_atoi(port_str);
	if (port < 1 || port > USHRT_MAX)
	{
		ft_printf("ERROR: %d: %s\n", port, PORT_ERR);
		return (0);
	}
	return ((uint16_t)port);
}

static char		*get_real_addr(char *addr)
{
	if (ft_strcmp(addr, "localhost") == 0)
	{
		if (g_client.addr_family == AF_INET6)
			return (ft_strdup("::1"));
		else
			return (ft_strdup("127.0.0.1"));
	}
	return (ft_strdup(addr));
}

static t_ex_ret	init(int argc, char **argv, uint16_t *port)
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
	g_client.mode = (opt_is_activated('a') == TRUE) ? ACTIVE : PASSIVE;
	g_client.addr_family = (opt_is_activated('6') == TRUE) ? AF_INET6 : AF_INET;
	g_client.addr = get_real_addr(argv[first_arg_index]);
	signal(SIGINT, sigint_handler);
	*port = get_port_uint16(argv[first_arg_index + 1]);
	if (*port == 0)
		return (FAILURE);
	return (SUCCESS);
}

static t_ex_ret	first_connection(void)
{
	char	reply_buff[REPLY_MAX_SIZE];

	ft_printf("Connection...\n");
	if (parse_and_display_reply(reply_buff) != 0)
	{
		ft_printf("Impossible to etablish a connection. Exiting...\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

int				main(int argc, char **argv)
{
	uint16_t	port;

	if (init(argc, argv, &port) == FAILURE)
		return (FAILURE);
	if ((g_client.sock = connect_to_server(g_client.addr, port)) == -1)
		return (FAILURE);
	if (first_connection() == FAILURE)
		return (FAILURE);
	return (communicate_with_server());
}
