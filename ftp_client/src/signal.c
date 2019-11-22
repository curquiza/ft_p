/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 14:47:39 by curquiza          #+#    #+#             */
/*   Updated: 2019/11/22 14:47:42 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	sigint_handler(int sig)
{
	(void)sig;
	ft_putchar('\n');
	quit_cmd("quit");
	exit(SUCCESS);
}
