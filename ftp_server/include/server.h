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

# define OPTIONS		"d"

# define MALLOC_ERR		"During malloc. Exiting..."
# define PORT_ERR		"Port number unavailable (1024-65335)"
# define LISTEN_NB		40
# define PORT_MIN_RANGE	1024
# define PORT_MAX_RANGE	USHRT_MAX
# define DEF_SIN_ADDR	INADDR_ANY
# define CMD_NB			3

# define RES_125	"125 Data connection already open. Transfer starting."

# define RES_220	"220 Service ready for new user."
# define RES_226	"226 Closing data connection."

# define RES_425	"425 Can't open data connection."
# define RES_426	"426 Connection closed; transfer aborted."
# define RES_451	"451 Requested action aborted: local error in processing."

# define RES_500	"500 Syntax error, command unrecognized."

/*
** STRUCTURES
*/

typedef struct		s_user
{
	int			num;
	int			ctrl_client_sock;
	int			dt_server_sock;
	int			dt_client_sock;
	uint16_t	dt_port;
}					t_user;

typedef struct		s_cmd
{
	char		*name;
	void		(*f)(t_user *user);
} 					t_cmd;

/*
** GLOBALS
*/

int			g_server_sock;
uint8_t		g_flags;
t_cmd		g_cmd_tab[CMD_NB];

/*
** FUNCTIONS
*/

t_ex_ret	activate_opt(char opt_letter);
t_bool		opt_is_activated(char opt_letter);
int			get_all_options(int argc, char **argv);

void		print_verbose_ss(char *s1, char *s2);
void		print_verbose_sis(char *s1, int i, char *s2);
void		print_verbose_siss(char *s1, int i, char *s2, char *s3);
void		print_ctrl_output(char *s1, int i, char *s2, char *s3);
void		print_data_output(char *s1, int i, char *s2, char *s3);
void		print_debug_output(char *s1, int i, char *s2, char *s3);


void		list_cmd(t_user *user);
void		pasv_cmd(t_user *user);
void		get_cmd(t_user *user);


void		usage(char *prgm);
t_ex_ret	close_server(int server_sock);

void		sigint_handler(int sig);
void		child_signals_handler(void);

int			create_server_socket(uint16_t port);
int			create_server_socket_on_random_port(uint16_t *assigned_port);
t_ex_ret	listen_to_clients(int server_sock);

void		send_oneline_reply_to_user(int client_sock, int client_num,
				char *str);

#endif
