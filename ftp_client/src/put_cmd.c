#include "client.h"

static int get_fd(char *input)
{
	int		fd;
	char	**args;

	args = ft_strsplit(input, ' ');
	fd = open(args[1], O_RDONLY);
	ft_tabdel(&args);
	if (fd == -1)
		return (print_and_return_neg(OPEN_ERR));
	return (fd);
}

static void	send_stor_command_to_server(char *input)
{
	char	**args;
	char	*cmd;

	args = ft_strsplit(input, ' ');
	cmd = ft_strjoin("STOR ", args[1]);
	send_to_server(cmd);
	free(cmd);
	ft_tabdel(&args);
}

static t_ex_ret	send_file_to_server(int dt_client_sock, int fd)
{
	int		ret;
	char	buff[READ_BUFF];

	while ((ret = read(fd, buff, READ_BUFF)) > 0)
		send(dt_client_sock, buff, ret, 0);
	if (ret == -1)
		return (print_and_return_failure(READ_ERR));
	return (SUCCESS);
}

static void manipulate_file(t_dt_socks dt, char *input, int fd)
{
	char	reply_buff[REPLY_MAX_SIZE];

	send_stor_command_to_server(input);
	if (parse_and_display_reply(reply_buff) != 0)
	{
		ft_printf("PUT command aborted.\n");
		close_data_connection(&dt);
		close(fd);
		return ;
	}
	if (send_file_to_server(dt.client_sock, fd) == FAILURE)
		ft_printf("PUT command aborted.\n");
	close_data_connection(&dt);
	close(fd);
	parse_and_display_reply(reply_buff);
}

void		put_cmd(char *input)
{
	t_dt_socks	dt;
	int			fd;

	if (has_only_one_arg(input) == FALSE)
	{
		ft_printf("%s\n", ARG_NB_ERR);
		ft_printf("Usage: %s\n", PUT_USAGE);
		return ;
	}
	if ((fd = get_fd(input)) == -1)
	{
		ft_printf("PUT command aborted.\n");
		return ;
	}
	if (etablish_data_connection(&dt) == FAILURE)
	{
		close_data_connection(&dt);
		ft_printf("PUT command aborted.\n");
		return ;
	}
	manipulate_file(dt, input, fd);
}
