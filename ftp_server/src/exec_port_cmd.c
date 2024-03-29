/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_port_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 12:28:12 by curquiza          #+#    #+#             */
/*   Updated: 2019/11/22 12:28:13 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void		get_addr(char **args, char *addr)
{
	int		len;

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
	len += ft_strlen(args[3]);
	addr[len] = 0;
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
	return (addr);
}

static int		print_and_ret_neg(char *str)
{
	print_debug_output(NULL, 0, str, NULL);
	return (-1);
}

static int		connect_to_user(char *addr, uint16_t port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	if ((proto = getprotobyname(TCP_PROTONAME)) == NULL)
		print_and_ret_neg(PROTOBYNAME_ERR);
	if ((sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)) < 0)
		print_and_ret_neg(SOCKET_ERR);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	if ((sin.sin_addr.s_addr = inet_addr(addr)) == INADDR_NONE)
		print_and_ret_neg(INET_ADDR_ERR);
	if ((connect(sock, (const struct sockaddr *)&sin, sizeof(sin))) == -1)
		print_and_ret_neg(CONNECT_ERR);
	return (sock);
}

void			exec_port_cmd(t_user *user, char *cmd)
{
	char		**arg_tab;
	char		addr[16];

	if ((arg_tab = port_get_arg_tab(cmd)) == NULL)
	{
		send_oneline_reply_to_user(user, RES_501);
		return ;
	}
	get_addr(arg_tab, addr);
	user->dt_port = get_port(arg_tab);
	ft_tabdel(&arg_tab);
	print_debug_output("Trying to connect to port", user->dt_port,
		"on address", addr);
	user->dt_client_sock = connect_to_user(addr, user->dt_port);
	if (user->dt_client_sock == -1)
		send_oneline_reply_to_user(user, RES_425);
	else
	{
		print_data_output("Connection etablished with user's port",
			user->dt_port, ": DT channel created [ACTIVE MODE]", NULL);
		send_oneline_reply_to_user(user, RES_200);
		user->mode = ACTIVE;
	}
}
