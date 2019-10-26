#include "server.h"

void	usage(char *prgm)
{
	ft_printf("Usage: %s: ./server [-d6] <port>\n", prgm);
	ft_printf("  -d : debug mode\n");
	ft_printf("  -6 : IPv6\n");
}

t_bool	is_dt_channel_open(t_user *user)
{
	if (user->dt_client_sock == -1)
		return (FALSE);
	return (TRUE);
}

t_bool	cmd_has_no_arg(t_user *user, char *cmd)
{
	char 	**args;
	t_bool	ret;

	args = ft_strsplit(cmd, ' ');
	ret = TRUE;
	if (!args || ft_tablen(args) != 1)
	{
		send_oneline_reply_to_user(user, RES_501);
		ret = FALSE;
	}
	ft_tabdel(&args);
	return (ret);
}

int		ret_err_neg(char *s)
{
	ft_printf("%s\n", s);
	return (-1);
}
