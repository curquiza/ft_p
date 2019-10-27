#include "client.h"

static t_bool	port_is_valid(char *arg)
{
	int32_t		port;

	if (ft_is_int(arg) == FALSE)
		return (FALSE);
	port = ft_atoi(arg);
	if (port < 1 || port > USHRT_MAX)
		return (FALSE);
	return (TRUE);
}

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

char		**get_args_for_inet6(char *cmd)
{
	char	**conn_args;

	conn_args = ft_strsplit(cmd, '|');
	if (!conn_args || ft_tablen(conn_args) != 3
		|| port_is_valid(conn_args[1]) == FALSE)
	{
		ft_tabdel(&conn_args);
		return (NULL);
	}
	return (conn_args);
}

char		**get_args_for_inet(char *cmd)
{
	char	**conn_args;
	char	**first_split;

	first_split = ft_strsplit(cmd, '(');
	if (!first_split || ft_tablen(first_split) != 2)
	{
		ft_tabdel(&first_split);
		return (NULL);
	}
	first_split[1][ft_strlen(first_split[1]) - 1] = '\0';
	conn_args = ft_strsplit(first_split[1], ',');
	if (!conn_args || ft_tablen(conn_args) != 6
		|| args_are_valid(conn_args) == FALSE)
	{
		ft_tabdel(&conn_args);
		return (NULL);
	}
	return (conn_args);
}

char		**get_connection_args_passive(char *cmd)
{
	if (g_addr_family == AF_INET6)
		return (get_args_for_inet6(cmd));
	return (get_args_for_inet(cmd));
}
