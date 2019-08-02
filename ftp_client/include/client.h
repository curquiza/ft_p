#ifndef CLIENT_H
# define CLIENT_H

# include "libft.h"
# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>

# define READ_CMD_ERR		"When reading user command"
# define READ_SERV_ASW_ERR	"When reading server answer"

void	usage(char *prgm);

#endif
