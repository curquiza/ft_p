/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_port_cmd_arg_tab.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 12:28:15 by curquiza          #+#    #+#             */
/*   Updated: 2019/11/22 12:28:16 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char			**port_get_arg_tab(char *cmd)
{
	char		**cmd_args;
	char		**arg_tab;

	cmd_args = ft_strsplit(cmd, ' ');
	if (!cmd_args || ft_tablen(cmd_args) != 2)
	{
		ft_tabdel(&cmd_args);
		return (NULL);
	}
	arg_tab = ft_strsplit(cmd_args[1], ',');
	ft_tabdel(&cmd_args);
	if (!arg_tab || ft_tablen(arg_tab) != 6 || args_are_valid(arg_tab) == FALSE)
	{
		ft_tabdel(&arg_tab);
		return (NULL);
	}
	return (arg_tab);
}
