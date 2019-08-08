#ifndef SERVER_H
# define SERVER_H

# include "libft.h"

# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>

# define OPTIONS		"v"

# define PORT_ERR		"Port number unavailable (1-65335)"
# define LISTEN_NB		40

/*
** GLOBALS
*/

int			g_server_sock;
uint8_t		g_flags;

/*
** FUNCTIONS
*/

t_ex_ret	activate_opt(char opt_letter);
t_bool		opt_is_activated(char opt_letter);

void		usage(char *prgm);
t_ex_ret	close_server(int server_sock);

void		sigint_handler(int sig);
void		child_signals_handler(void);

int			create_server(uint16_t port);
void		listen_to_clients(int server_sock);

#endif
