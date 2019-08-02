#ifndef SERVER_H
# define SERVER_H

# include "libft.h"

# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>

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

t_ex_ret	init(int argc, char **argv);

#endif
