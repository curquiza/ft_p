#ifndef CLIENT_H
# define CLIENT_H

# include "libft.h"
# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>

# define OPTIONS			"6"

# define ADDR_MAX_SIZE		15

# define READ_CMD_ERR		"When reading user command"
# define READ_SERV_ASW_ERR	"When reading server reply"

# define PORT_ERR			"Port number unavailable (1-65335)"
# define SOCKET_ERR			"ERROR: socket syscall."
# define CONNECT_ERR		"ERROR: connect syscall."
# define INET_ERR			"ERROR: inet_addr."


/*
** GLOBALS
*/
uint8_t			g_flags;
sa_family_t		g_addr_family;

/*
** FUNCTION PROTOTYPES
*/
void		usage(char *prgm);

t_ex_ret	activate_opt(char opt_letter);
t_bool		opt_is_activated(char opt_letter);
int			get_all_options(int argc, char **argv);

int			connect_to_server(char *addr, uint16_t port);

#endif
