#include "client.h"

static int		ret_err_neg(char *s)
{
	ft_dprintf(2, "Error: %s\n", s);
	return (-1);
}

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


static t_ex_ret	init(int argc, char **argv, char *addr, int *port)
{
	int		first_arg_index;

	if (argc < 3)
	{
		usage(argv[0]);
		return (FAILURE);
	}
	g_flags = 0;
	if ((first_arg_index = get_all_options(argc, argv)) == -1)
		return (FAILURE);
	if (first_arg_index + 2 != argc)
	{
		usage(argv[0]);
		return (FAILURE);
	}
	ft_bzero(addr, ADDR_MAX_SIZE + 1);
	ft_strncpy(addr, argv[first_arg_index], ADDR_MAX_SIZE);
	*port = get_port_uint16(argv[first_arg_index + 1]);
	if (*port == 0)
		return (FAILURE);
	return (SUCCESS);
}

int		create_client(char *addr, int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	if ((proto = getprotobyname("tcp")) == NULL)
		return (ret_err_neg("During getprotobyname"));
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(addr);
	if ((connect(sock, (const struct sockaddr *)&sin, sizeof(sin))) == -1)
		return (ret_err_neg("During connect"));
	return (sock);
}

t_ex_ret	communicate_with_server(int sock)
{
	char	*cmd;
	char	*buff;
	int		ret;

	buff = NULL;
	while (1)
	{
		// GET USER COMMAND
		ft_printf("Your command: ");
		ret = get_next_line(0, &buff);
		if (ret == -1)
			return (ft_ret_err(READ_CMD_ERR));
		else if (ret == 0)
			break ;
		cmd = ft_strjoin(buff, "\n");

		// CHECK QUIT COMMAND
		if (ft_strcmp(cmd, "quit\n") == 0)
		{
			free(buff);
			free(cmd);
			break ;
		}

		// WRITE TO SERVER
		send(sock, cmd, ft_strlen(cmd), 0);
		free(buff);
		free(cmd);

		// READ SERVER reply
		char	buff2[500001];
		ret = recv(sock, &buff2, 500000, 0);
		// ret = read(sock, &buff2, 500000);
		buff2[ret] = '\0';
		if (ret == -1)
			return (ft_ret_err(READ_SERV_ASW_ERR));
		else if (ret == 0)
			break ;
		ft_printf("Server reply: %s", buff2);
		// ft_printf("(recv return = %d)\n", ret);
	}
	return (SUCCESS);
}

int		main(int argc, char **argv)
{
	int		sock;
	// int		ret;
	char	addr[ADDR_MAX_SIZE + 1];
	int		port;

	if (init(argc, argv, addr, &port) == FAILURE)
		return (FAILURE);
	if ((sock = create_client(addr, port)) == -1)
		return (FAILURE);

	// ret = communicate_with_server(sock);

	// printf("Quitting FTP Client...\n");
	// close(sock);
	// return (ret);
}
