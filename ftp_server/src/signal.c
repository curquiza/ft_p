/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 12:29:11 by curquiza          #+#    #+#             */
/*   Updated: 2019/11/22 12:29:11 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	sigint_handler(int sig)
{
	(void)sig;
	exit(close_server(g_server_sock));
}

void	sigchld_handler(int sig)
{
	(void)sig;
	g_user_nb--;
	print_debug_output("Number of users currently connected :", g_user_nb,
		NULL, NULL);
}

void	child_signals_handler(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
}
