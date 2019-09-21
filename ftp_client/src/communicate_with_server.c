#include "client.h"

void	communicate_with_server(int sock)
{
	char	*cmd;
	char	*buff;
	int		ret;

	buff = NULL;
	while (1)
	{
		// GET USER COMMAND
		ft_printf("Your command: ");
		ret = get_next_line(0, &buff);
		if (ret == -1)
			; // return (ft_ret_err(READ_CMD_ERR));
		else if (ret == 0)
			break ;
		cmd = ft_strjoin(buff, "\n");

		// CHECK QUIT COMMAND
		if (ft_strcmp(cmd, "quit\n") == 0)
		{
			free(buff);
			free(cmd);
			break ;
		}

		// WRITE TO SERVER
		send(sock, cmd, ft_strlen(cmd), 0);
		free(buff);
		free(cmd);

		// READ SERVER reply
		char	buff2[500001];
		ret = recv(sock, &buff2, 500000, 0);
		// ret = read(sock, &buff2, 500000);
		buff2[ret] = '\0';
		if (ret == -1)
			; // return (ft_ret_err(READ_SERV_ASW_ERR));
		else if (ret == 0)
			break ;
		ft_printf("Server reply: %s", buff2);
		// ft_printf("(recv return = %d)\n", ret);
	}
	quit_cmd(NULL);
}
