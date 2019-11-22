/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_arg_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 14:47:02 by curquiza          #+#    #+#             */
/*   Updated: 2019/11/22 14:47:03 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

t_bool	has_no_arg(char *input)
{
	char	**args_tab;
	t_bool	rslt;

	if (!input)
		return (FALSE);
	rslt = TRUE;
	args_tab = ft_strsplit(input, ' ');
	if (!args_tab || ft_tablen(args_tab) != 1)
		rslt = FALSE;
	ft_tabdel(&args_tab);
	return (rslt);
}

t_bool	has_only_one_arg(char *input)
{
	char	**args_tab;
	t_bool	rslt;

	if (!input)
		return (FALSE);
	rslt = TRUE;
	args_tab = ft_strsplit(input, ' ');
	if (!args_tab || ft_tablen(args_tab) != 2)
		rslt = FALSE;
	ft_tabdel(&args_tab);
	return (rslt);
}

t_bool	has_zero_or_one_arg(char *input)
{
	return (has_no_arg(input) || has_only_one_arg(input));
}

t_bool	has_one_or_two_args(char *input)
{
	char	**args_tab;
	t_bool	rslt;

	if (has_only_one_arg(input))
		return (TRUE);
	if (!input)
		return (FALSE);
	rslt = TRUE;
	args_tab = ft_strsplit(input, ' ');
	if (!args_tab || ft_tablen(args_tab) != 3)
		rslt = FALSE;
	ft_tabdel(&args_tab);
	return (rslt);
}
