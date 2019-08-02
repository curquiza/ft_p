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
	listen(sock, 10);
	return (sock);
}

void	communicate_with_new_client(int client_sock)
{
	char				buff[1024];

	while (read(client_sock, buff, 1023) > 0)
	{
		printf("client request = %s", buff);
		printf("------------------\n");
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

	while (1)
	{
		client_sock = accept(server_sock, (struct sockaddr *)&client_sin, &client_size);
		pid = fork();
		if (pid == 0)
		{
			communicate_with_new_client(client_sock);
		}
		else
		{
			close(client_sock);
		}
	}
}

int		main(int argc, char **argv)
{
	int					server_sock;
	int					port;

	if (argc != 2)
	{
		usage(argv[0]);
		exit(1);
	}

	port = ft_atoi(argv[1]);
	if ((server_sock = create_server(port)) == -1)
		return (FAILURE);

	printf("server socket = %d\n", server_sock);
	printf("- - - - - - - - - - - -\n");
	listen_to_clients(server_sock);

	close(server_sock);
	return (SUCCESS);
}
