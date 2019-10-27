#include "client.h"

static void	read_and_display_ls(int dt_client_sock)
{
	int		ret;
	char	buff[READ_BUFF + 1];

	while ((ret = recv(dt_client_sock, buff, READ_BUFF, 0)) > 0)
	{
		buff[ret] = '\0';
		ft_printf(buff);
	}
	if (ret == -1)
		ft_printf("Error during ls output display.");
}

static void	send_list_command_to_server(char *input)
{
	char	**args;
	char	*cmd;

	args = ft_strsplit(input, ' ');
	if (args[1] == NULL)
		send_to_server("LIST");
	else
	{
		cmd = ft_strjoin("LIST ", args[1]);
		send_to_server(cmd);
		free(cmd);
	}
	ft_tabdel(&args);
}

void		ls_cmd(char *input)
{
	char		reply_buff[REPLY_MAX_SIZE];
	t_dt_socks	dt;

	if (has_zero_or_one_arg(input) == FALSE)
	{
		ft_printf("%s\n", ARG_NB_ERR);
		ft_printf("Usage: %s\n", LS_USAGE);
		return ;
	}
	if (etablish_data_connection(&dt) == FAILURE)
	{
		close_data_connection(&dt);
		ft_printf("LS command aborted.\n");
		return ;
	}
	send_list_command_to_server(input);
	if (parse_and_display_reply(reply_buff) != 0)
	{
		close_data_connection(&dt);
		ft_printf("LS command aborted.\n");
		return ;
	}
	read_and_display_ls(dt.client_sock);
	parse_and_display_reply(reply_buff);
	close_data_connection(&dt);
}
