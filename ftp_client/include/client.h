#ifndef CLIENT_H
# define CLIENT_H

# include "libft.h"
# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>

# define OPTIONS			"6a"

# define LISTEN_NB			40
# define TCP_PROTONAME		"tcp"
# define REPLY_MAX_SIZE		1000
# define PORT_MIN_RANGE		1024
# define DEFAULT_SIN_ADDR	INADDR_ANY
# define DEFAULT_SIN6_ADDR	in6addr_any
# define PORT_MAX_RANGE		USHRT_MAX
# define READ_BUFF			10000

# define READ_CMD_ERR		"When reading user command. Exiting..."
# define MALLOC_ERR			"ERROR: malloc. Exiting..."

# define PORT_ERR			"Port number unavailable (1-65335)"
# define PROTOBYNAME_ERR	"ERROR: getprotobyname function."
# define SOCKET_ERR			"ERROR: socket syscall."
# define CONNECT_ERR		"ERROR: connect syscall."
# define INET_PTON_ERR		"ERROR: inet_pton. IPv6 address not parsable."
# define INET_ADDR_ERR		"ERROR: inet_addr."
# define UNKNOWN_CMD_ERR	"ERROR: Unknown command."
# define ARG_NB_ERR			"ERROR: Wrong number of argument."
# define REP_BAD_FORMAT_ERR	"ERROR: Reply bad formatted."
# define DATA_CONN_ERR		"ERROR: Impossible to etablish data connection."

# define HELP_USAGE			"help"
# define QUIT_USAGE			"quit"
# define CD_USAGE			"cd <path>"
# define PWD_USAGE			"pwd"
# define LS_USAGE			"ls [path]"
# define GET_USAGE			"get <filename> [new_filename]"
# define PUT_USAGE			"put <filename>"
# define MODE_USAGE			"mode"
# define PASS_USAGE			"pass"

# define HELP_DES			"Display all commands."
# define QUIT_DES			"Close the connection and exit the client."
# define CD_DES				"Change the current working directory on the server."
# define PWD_DES			"Get the current working directory on the server."
# define LS_DES				"Execute ls command."
# define GET_DES			"Downlaod the file on the server."
# define PUT_DES			"Upload the file on the server."
# define MODE_DES			"Display the current mode (active/passive)."
# define PASS_DES			"On/off the passive mode."

# define CMD_NB				7

/*
** STRUCTURES
*/
typedef struct	s_cmd
{
	char		*name;
	void		(*f)(char *cmd);
	char		*usage;
	char		*description;
}				t_cmd;

typedef enum	e_mode
{
	PASSIVE,
	ACTIVE
}				t_mode;

typedef struct	s_dt_socks
{
	int			server_sock;
	int			client_sock;
}				t_dt_socks;

/*
** GLOBALS
*/
uint8_t			g_flags;
sa_family_t		g_addr_family;
t_mode			g_mode;
int				g_sock;
char			*g_addr;
char			*g_current_path;
t_bool			g_run;
t_cmd			g_cmd_tab[CMD_NB];

/*
** FUNCTION PROTOTYPES
*/
void		usage(char *prgm);
t_ex_ret	print_and_return_failure(char *str);
int			print_and_return_neg(char *str);
t_bool		has_no_arg(char *input);
t_bool		has_only_one_arg(char *input);
t_bool		has_zero_or_one_arg(char *input);

t_ex_ret	activate_opt(char opt_letter);
t_bool		opt_is_activated(char opt_letter);
int			get_all_options(int argc, char **argv);

void		sigint_handler(int sig);

void		send_to_server(char *str);

int			parse_and_display_reply(char *reply_buff);

char		**get_connection_args_passive(char *cmd);
t_ex_ret	etablish_data_connection_passive(t_dt_socks *dt);

int			create_server_socket_on_valid_port(uint16_t *dt_port);
t_ex_ret	etablish_data_connection_active(t_dt_socks *dt);

t_ex_ret	etablish_data_connection(t_dt_socks *dt);
void		close_data_connection(t_dt_socks *dt);

int			connect_to_server(char *addr, uint16_t port);
t_ex_ret	communicate_with_server(void);

void		help_cmd(char *input);
void		ls_cmd(char *input);
void		pass_cmd(char *input);
void		mode_cmd(char *input);
void		quit_cmd(char *input);
void		cd_cmd(char *input);
void		pwd_cmd(char *input);

#endif
