#include "server.h"

static int		ret_err_neg(char *s)
{
	ft_dprintf(2, "Error: %s\n", s);
	return (-1);
}

int		create_server(int 	port)
{
	int 				sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;			// /usr/include/netinet/in.h

	if ((proto = getprotobyname("tcp")) == NULL)
		return (ret_err_neg("During getprotobyname"));
	if ((sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)) == -1)
		return (ret_err_neg("During socket server creation"));
	sin.sin_family = AF_INET;  // adress family internet
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
		return (ret_err_neg("During binding"));
	listen(sock, LISTEN_NB);
	return (sock);
}

void	communicate_with_new_client(int client_sock)
{
	char				buff[1024];

	while (read(client_sock, buff, 1023) > 0)
	{
		printf("------------------\nclient request = %s", buff);
		ft_bzero(&buff, 1024);
	}
	close(client_sock);
}

void	listen_to_clients(int server_sock)
{
	pid_t				pid;
	int					client_sock;
	unsigned int		client_size;
	struct sockaddr_in	client_sin;
	int					client_num;

	client_num = 1;
	while (1)
	{
		client_sock = accept(server_sock, (struct sockaddr *)&client_sin, &client_size);
		pid = fork();
		if (pid == 0)
		{
			child_signals_handler();
			printf("------------------\nClient number %d connected\n", client_num);
			communicate_with_new_client(client_sock);
		}
		else
		{
			close(client_sock);
		}
		client_num++;
	}
}

uint16_t		get_port(char *port_str)
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

int		main(int argc, char **argv)
{
	uint16_t	port;

	if (init(argc, argv) == FAILURE)
		return (FAILURE);
	port = get_port(argv[1]);
	if (port == 0)
		return (FAILURE);
	if ((g_server_sock = create_server(port)) == -1)
		return (FAILURE);

	printf("FTP Server open on port %d\n", port);
	listen_to_clients(g_server_sock);

	return (SUCCESS);
}
