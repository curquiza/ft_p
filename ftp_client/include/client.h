#ifndef CLIENT_H
# define CLIENT_H

# include "libft.h"
# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>

# define OPTIONS			"6"

# define ADDR_MAX_SIZE		15

# define READ_CMD_ERR		"When reading user command. Exiting..."
# define READ_SERV_ASW_ERR	"When reading server reply. Exiting..."
# define MALLOC_ERR			"ERROR: malloc. Exiting..."

# define PORT_ERR			"Port number unavailable (1-65335)"
# define SOCKET_ERR			"ERROR: socket syscall."
# define CONNECT_ERR		"ERROR: connect syscall."
# define INET_PTON_ERR		"ERROR: inet_pton. IPv6 address not parsable."
# define INET_ADDR_ERR		"ERROR: inet_addr."
# define UNKNOWN_CMD_ERR	"ERROR: Unknown command."

# define CMD_NB				1

/*
** STRUCTURES
*/
typedef struct	s_cmd
{
	char		*name;
	void		(*f)(char *cmd);
}				t_cmd;

/*
** GLOBALS
*/
uint8_t			g_flags;
sa_family_t		g_addr_family;
int				g_sock;
t_bool			g_run;
t_cmd			g_cmd_tab[CMD_NB];

/*
** FUNCTION PROTOTYPES
*/
void		usage(char *prgm);

t_ex_ret	activate_opt(char opt_letter);
t_bool		opt_is_activated(char opt_letter);
int			get_all_options(int argc, char **argv);

void		sigint_handler(int sig);

int			connect_to_server(char *addr, uint16_t port);
t_ex_ret	communicate_with_server(void);

void		quit_cmd(char *input);

#endif
