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

# define OPTIONS			"d6"

# define PORT_ERR			"Port number unavailable (1024-65335)"
# define ROOT_PATH_ERR		"ERROR: when getting server root path. Exiting..."
# define MALLOC_ERR			"ERROR: malloc. Exiting..."
# define SOCKET_ERR			"ERROR: socket syscall."
# define ACCEPT_ERR			"ERROR: accept syscall."
# define CONNECT_ERR		"ERROR: connect syscall."
# define BIND_ERR			"ERROR: bind syscall."
# define LISTEN_ERR			"ERROR: listen syscall."
# define CHDIR_ERR			"ERROR: chdir syscall."
# define PROTOBYNAME_ERR	"ERROR: getprotobyname function."
# define INET_ERR			"ERROR: inet_addr."
# define NO_PORT_ERR		"ERROR: no port available to create DT channel."
# define LS_ERR				"ERROR: during ls execution process."

# define LISTEN_NB			40
# define PORT_MIN_RANGE		1024
# define PORT_MAX_RANGE		USHRT_MAX
# define DEFAULT_SIN_ADDR	INADDR_ANY
# define DEFAULT_SIN6_ADDR	in6addr_any
# define TCP_PROTONAME		"tcp"
# define READ_BUFF			10000
# define CMD_NB				9
# define MAX_USERS			3

# define RES_125	"125 Data connection already open. Transfer starting."

# define RES_200	"200 Command okay."
# define RES_220	"220 Service ready for new user."
# define RES_226	"226 Closing data connection."

# define RES_425	"425 Can't open data connection."
# define RES_426	"426 Connection closed; transfer aborted."
# define RES_451	"451 Requested action aborted: local error in processing."

# define RES_500	"500 Syntax error, command unrecognized."
# define RES_501	"501 Syntax error in parameters or arguments."
# define RES_550_1	"550 Requested action not taken."
# define RES_550_2	"550 File unavailable."
# define RES_550_3	"550 Not a directory."
# define RES_550_4	"550 Requested action not taken. Too many clients connected."

/*
** STRUCTURES
*/

typedef enum	e_mode
{
	NONE,
	PASSIVE,
	ACTIVE
}				t_mode;

typedef struct	s_user
{
	int			num;
	t_mode		mode;
	int			ctrl_client_sock;
	int			dt_server_sock;
	int			dt_client_sock;
	uint16_t	dt_port;
}				t_user;

typedef struct	s_cmd
{
	char		*name;
	void		(*f)(t_user *user, char *cmd);
}				t_cmd;

typedef struct			s_chunk
{
	int				size;
	char			content[READ_BUFF];
	struct s_chunk	*next;
}						t_chunk;

/*
** GLOBALS
*/

uint8_t			g_flags;
int				g_server_sock;
sa_family_t		g_addr_family;
int				g_user_nb;
t_cmd			g_cmd_tab[CMD_NB];
char			*g_root_path;

/*
** FUNCTIONS
*/

t_ex_ret		activate_opt(char opt_letter);
t_bool			opt_is_activated(char opt_letter);
int				get_all_options(int argc, char **argv);

void			usage(char *prgm);
t_bool			is_dt_channel_open(t_user *user);
t_bool			cmd_has_no_arg(t_user *user, char *cmd);

void			sigint_handler(int sig);
void			sigchld_handler(int sig);
void			child_signals_handler(void);

char			*get_current_wd_in_server(void);
char			*get_valid_path_from_user_input(char *path);

void			clean_list(t_chunk **list);
void			list_push_back(t_chunk **alst, t_chunk *new, t_chunk **end);
t_chunk			*new_chunk(int size, char *content);
char			*get_file_content(t_user *user, int *size);

t_ex_ret		listen_to_clients(int server_sock);

t_ex_ret		bind_server(int sock, uint16_t port);

void			send_oneline_reply_to_user(t_user *user, char *str);

void			exec_pasv_cmd(t_user *user, char *cmd);
void			exec_epsv_cmd(t_user *user, char *cmd);
void			exec_port_cmd(t_user *user, char *cmd);
void			exec_list_cmd(t_user *user, char *cmd);
void			exec_retr_cmd(t_user *user, char *cmd);
void			exec_stor_cmd(t_user *user, char *cmd);
void			exec_pwd_cmd(t_user *user, char *cmd);
void			exec_cwd_cmd(t_user *user, char *cmd);
void			exec_type_cmd(t_user *user, char *cmd);

t_ex_ret		close_server(int server_sock);
void			close_user_data_channel(t_user *user);

void			print_ctrl_output(char *s1, int i, char *s2, char *s3);
void			print_data_output(char *s1, int i, char *s2, char *s3);
void			print_debug_output(char *s1, int i, char *s2, char *s3);
void			log_data_sent_into_dt_channel(t_user *user, char *s);
void			log_data_received_from_dt_channel(t_user *user, char *s);

#endif
