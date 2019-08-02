#include "server.h"

static void	communicate_with_new_client(int client_sock)
{
	char				buff[1024];

	while (read(client_sock, buff, 1023) > 0)
	{
		printf("------------------\nclient request = %s", buff);
		ft_bzero(&buff, 1024);
	}
	close(client_sock);
}

void		listen_to_clients(int server_sock)
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
