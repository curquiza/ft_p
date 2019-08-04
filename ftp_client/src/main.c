#include "client.h"

static int		ret_err_neg(char *s)
{
	ft_dprintf(2, "Error: %s\n", s);
	return (-1);
}

int		create_client(char *addr, int port)
{
	int		sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;			// /usr/include/netinet/in.h

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

		// READ SERVER ANSWER
		char	buff2[500001];
		ret = recv(sock, &buff2, 500000, 0);
		// ret = read(sock, &buff2, 500000);
		buff2[ret] = '\0';
		if (ret == -1)
			return (ft_ret_err(READ_SERV_ASW_ERR));
		else if (ret == 0)
			break ;
		ft_printf("Server answer: %s", buff2);
		ft_printf("(recv return = %d)\n", ret);
	}
	return (SUCCESS);
}

int		main(int argc, char **argv)
{
	int		sock;
	int		ret;

	if (argc != 3)
	{
		usage(argv[0]);
		return (FAILURE);
	}
	sock = create_client(argv[1], ft_atoi(argv[2]));
	if (sock == -1)
		return (FAILURE);

	ret = communicate_with_server(sock);

	printf("Quitting FTP Client...\n");
	close(sock);
	return (ret);
}
