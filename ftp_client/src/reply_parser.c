#include "client.h"

/*
** 0 : Reply ok
** 1 : Reply error
** -1 : Error during reply parsing
*/
static int	parse_reply(char *reply)
{
	if (!reply || !reply[0])
	{
		ft_printf("%s\n", REP_BAD_FORMAT_ERR);
		return (-1);
	}
	if (reply[0] == '1' || reply[0] == '2' || reply[0] == '3')
	{
		ft_printf("SUCCESS: %s\n", reply);
		return (0);
	}
	else if (reply[0] == '4' || reply[0] == '5')
	{
		ft_printf("ERROR: %s\n", reply);
		return (1);
	}
	else
	{
		ft_printf("%s\n", REP_BAD_FORMAT_ERR);
		return (-1);
	}
}

int			parse_and_display_reply(char *reply_buff)
{
	int		len;

	ft_bzero(reply_buff, REPLY_MAX_SIZE);
	if ((len = recv(g_sock, reply_buff, REPLY_MAX_SIZE, 0)) > 0)
	{
		if (len >= 2 && reply_buff[len - 2] == '\r')
			reply_buff[len - 2] = '\0';
		else if (len >= 1 && reply_buff[len - 1] == '\n')
			reply_buff[len - 1] = '\0';
		else
		{
			ft_printf("%s\n", REP_BAD_FORMAT_ERR);
			return (-1);
		}
	}
	return (parse_reply(reply_buff));
}
