#ifndef CLIENT_H
# define CLIENT_H

# include "libft.h"
# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>

# define OPTIONS			"6"

# define ADDR_MAX_SIZE		15
# define PORT_MAX_SIZE		5

# define READ_CMD_ERR		"When reading user command"
# define READ_SERV_ASW_ERR	"When reading server reply"


/*
** GLOBALS
*/
uint8_t			g_flags;

/*
** FUNCTION PROTOTYPES
*/
void		usage(char *prgm);

t_ex_ret	activate_opt(char opt_letter);
t_bool		opt_is_activated(char opt_letter);
int			get_all_options(int argc, char **argv);

#endif
