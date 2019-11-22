/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 14:47:09 by curquiza          #+#    #+#             */
/*   Updated: 2019/11/22 14:47:10 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

t_ex_ret	activate_opt(char opt_letter)
{
	char		*opt;
	uint32_t	opt_mask;

	if (!(opt = ft_strchr(OPTIONS, opt_letter)))
	{
		ft_printf("Error: -%c: Invalid option\n", opt_letter);
		return (FAILURE);
	}
	opt_mask = (1 << (opt - OPTIONS));
	g_flags |= opt_mask;
	return (SUCCESS);
}

t_bool		opt_is_activated(char opt_letter)
{
	char		*opt;
	uint32_t	opt_mask;

	if (!(opt = ft_strchr(OPTIONS, opt_letter)))
		return (FALSE);
	opt_mask = (1 << (opt - OPTIONS));
	return ((g_flags & opt_mask) == opt_mask);
}

/*
** Parses all options and returns the first argument index.
** Returns -1 if any error.
*/

int			get_all_options(int argc, char **argv)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if (*argv[i] != '-')
			return (i);
		if (ft_strcmp(argv[i], "--") == 0)
			return (i + 1);
		(argv[i])++;
		while (*argv[i])
		{
			if (activate_opt(*argv[i]) == FAILURE)
				return (-1);
			(argv[i])++;
		}
		i++;
	}
	return (i);
}
