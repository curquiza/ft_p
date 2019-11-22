/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 14:47:00 by curquiza          #+#    #+#             */
/*   Updated: 2019/11/22 14:47:00 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void		usage(char *prgm)
{
	ft_printf("Usage: %s: ./client [-6] <address> <port>\n", prgm);
	ft_printf("  -6 : IPv6\n");
	ft_printf("  -a : force active mode\n");
}

t_ex_ret	print_and_return_failure(char *str)
{
	ft_printf("%s\n", str);
	return (FAILURE);
}

int			print_and_return_neg(char *str)
{
	ft_printf("%s\n", str);
	return (-1);
}
