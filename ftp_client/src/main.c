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
	int		read_ret;

	buff = NULL;
	while (1)
	{
		// FGET USER COMMAND
		ft_printf("Your command: ");
		read_ret = get_next_line(0, &buff);
		if (read_ret == -1)
			return (ft_ret_err(READ_CMD_ERR));
		else if (read_ret == 0)
			break ;

		// CHECK QUIT COMMAND
		if (ft_strcmp(buff, "quit") == 0)
		{
			free(buff);
			break ;
		}

		// WRITE TO SERVER
		cmd = ft_strjoin(buff, "\n");
		write(sock, cmd, ft_strlen(cmd));
		free(buff);
		free(cmd);

		// READ SERVER QNSWER
		read_ret = get_next_line(sock, &buff);
		if (read_ret == -1)
			return (ft_ret_err(READ_SERV_ASW_ERR));
		else if (read_ret == 0)
			break ;
		ft_printf("Server answer: %s\n", buff);
		free(buff);
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
