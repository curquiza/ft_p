#ifndef SERVER_H
# define SERVER_H

# include "libft.h"

# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <limits.h>

# define PORT_ERR		"Port number unavailable (1-65335)"
# define LISTEN_NB		40

/*
** GLOBALS
*/

int			g_server_sock;

/*
** FUNCTIONS
*/

void		usage(char *prgm);

void		sigint_handler(int sig);
void		child_signals_handler(void);

int			create_server(uint16_t port);
void		listen_to_clients(int server_sock);

#endif