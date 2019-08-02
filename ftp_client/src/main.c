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

int		main(int argc, char **argv)
{
	int		sock;

	if (argc != 3)
	{
		usage(argv[0]);
		return (FAILURE);
	}
	sock = create_client(argv[1], ft_atoi(argv[2]));
	if (sock == -1)
		return (FAILURE);
	write(sock, "lol\n", 4);
	close(sock);
	return (SUCCESS);
}
