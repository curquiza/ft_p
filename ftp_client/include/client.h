#ifndef CLIENT_H
# define CLIENT_H

# include "libft.h"
# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>

# define OPTIONS			"6"

# define ADDR_MAX_SIZE		15
# define REPLY_MAX_SIZE		1000

# define READ_CMD_ERR		"When reading user command. Exiting..."
# define MALLOC_ERR			"ERROR: malloc. Exiting..."

# define PORT_ERR			"Port number unavailable (1-65335)"
# define SOCKET_ERR			"ERROR: socket syscall."
# define CONNECT_ERR		"ERROR: connect syscall."
# define INET_PTON_ERR		"ERROR: inet_pton. IPv6 address not parsable."
# define INET_ADDR_ERR		"ERROR: inet_addr."
# define UNKNOWN_CMD_ERR	"ERROR: Unknown command."
# define ARG_NB_ERR			"ERROR: Wrong number of argument."
# define REP_BAD_FORMAT_ERR	"ERROR: Reply bad formatted."

# define HELP_USAGE			"help"
# define QUIT_USAGE			"quit"
# define CD_USAGE			"cd <path>"
# define PWD_USAGE			"pwd"
# define LS_USAGE			"ls [path]"
# define GET_USAGE			"get <filename> [new_filename]"
# define PUT_USAGE			"put <filename>"

# define HELP_DES			"Display all commands."
# define QUIT_DES			"Close the connection and exit the client."
# define CD_DES				"Change the current working directory on the server."
# define PWD_DES			"Get the current working directory on the server."
# define LS_DES				"Execute ls command."
# define GET_DES			"Downlaod the file on the server."
# define PUT_DES			"Upload the file on the server."

# define CMD_NB				4

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
char			*g_current_path;
t_bool			g_run;
t_cmd			g_cmd_tab[CMD_NB];

/*
** FUNCTION PROTOTYPES
*/
void		usage(char *prgm);
t_bool		has_no_arg(char *input);
t_bool		has_only_one_arg(char *input);

t_ex_ret	activate_opt(char opt_letter);
t_bool		opt_is_activated(char opt_letter);
int			get_all_options(int argc, char **argv);

void		sigint_handler(int sig);

void		send_to_server(char *str);

int			parse_and_display_reply(char *reply_buff);

int			connect_to_server(char *addr, uint16_t port);
t_ex_ret	communicate_with_server(void);

void		help_cmd(char *input);
void		quit_cmd(char *input);
void		cd_cmd(char *input);
void		pwd_cmd(char *input);

#endif
