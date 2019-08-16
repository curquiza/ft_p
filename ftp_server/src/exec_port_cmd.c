#include "server.h"

static t_bool	args_are_valid(char **args)
{
	int		arg_int;

	while (*args)
	{
		if (ft_is_int(*args) == FALSE)
			return (FALSE);
		arg_int = ft_atoi(*args);
		if (arg_int < 0 || arg_int > UCHAR_MAX)
			return (FALSE);
		args++;
	}
	return (TRUE);
}

static char	*get_addr(char **args)
{
	char	*addr;
	int		len;

	addr = ft_strnew(15);
	ft_strcpy(addr, args[0]);
	len = ft_strlen(args[0]) + 1;
	addr[len - 1] = '.';
	ft_strcpy(addr + len, args[1]);
	len += ft_strlen(args[1]) + 1;
	addr[len - 1] = '.';
	ft_strcpy(addr + len, args[2]);
	len += ft_strlen(args[2]) + 1;
	addr[len - 1] = '.';
	ft_strcpy(addr + len, args[3]);
	return (addr);
}

static uint16_t	get_port(char **args)
{
	uint16_t	addr;
	int			tmp;

	addr = 0;
	tmp = ft_atoi(args[4]);
	addr = (tmp & 0x000000ff);
	addr = addr << 8;
	tmp = ft_atoi(args[5]);
	addr |= (tmp & 0x000000ff);
	return addr;
}

static int	connect_to_user(char *addr, uint16_t port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	if ((proto = getprotobyname("tcp")) == NULL)
	{
		print_debug_output(NULL, 0, "Error during getprotobyname", NULL);
		return (-1);
	}
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(addr);
	if ((connect(sock, (const struct sockaddr *)&sin, sizeof(sin))) == -1)
	{
		print_debug_output(NULL, 0, "Error during connect", NULL);
		return (-1);
	}
	return (sock);
}

void	exec_port_cmd(t_user *user, char *cmd)
{
	char		*arg_addr;
	char		*arg;
	char		**subargs;
	char		*addr;

	arg_addr = ft_strchr(cmd, ' ');
	if (arg_addr == NULL)
	{
		send_oneline_reply_to_user(user->ctrl_client_sock, user->num, RES_501);
		return ;
	}
	arg = ft_strtrim(arg_addr);
	subargs = ft_strsplit(arg, ',');
	free(arg);
	if (subargs == NULL
		|| ft_tablen(subargs) != 6
		|| args_are_valid(subargs) == FALSE)
	{
		send_oneline_reply_to_user(user->ctrl_client_sock, user->num, RES_501);
		free(subargs);
		return ;
	}
	addr = get_addr(subargs);
	user->dt_port = get_port(subargs);
	print_debug_output("Trying to connect to port", user->dt_port, "on address", addr);
	user->dt_client_sock = connect_to_user(addr, user->dt_port);
	if (user->dt_client_sock == -1)
		send_oneline_reply_to_user(user->ctrl_client_sock, user->num, RES_425);
	else
	{
		print_data_output("Connection etablished with user's port", user->dt_port, ": DT channel created [ACTIVE MODE]", NULL);
		send_oneline_reply_to_user(user->ctrl_client_sock, user->num, RES_200);
		user->mode = ACTIVE;
	}
	free(subargs);
	free(addr);
};
