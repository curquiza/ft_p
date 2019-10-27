#include "client.h"

static int		get_fd(char *input)
{
	int		fd;
	char	**args;

	args = ft_strsplit(input, ' ');
	if (ft_tablen(args) == 2)
		fd = open(args[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(args[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ft_tabdel(&args);
	if (fd == -1)
		return (print_and_return_neg(CREATE_FILE_ERR));
	return (fd);
}

static void		send_retr_cmd_to_server(char *input)
{
	char	**args;
	char	*cmd;

	args = ft_strsplit(input, ' ');
	cmd = ft_strjoin("RETR ", args[1]);
	send_to_server(cmd);
	free(cmd);
	ft_tabdel(&args);
}

static t_ex_ret	get_file_from_server(int dt_client_sock, int fd)
{
	int	ret;
	char	buff[READ_BUFF];

	while ((ret = recv(dt_client_sock, buff, READ_BUFF, 0)) > 0)
		write(fd, buff, ret);
	if (ret == -1)
		return (print_and_return_failure(READ_ERR));
	return (SUCCESS);
}

static void		manipulate_file(t_dt_socks dt, char *input, int fd)
{
	char	reply_buff[REPLY_MAX_SIZE];

	send_retr_cmd_to_server(input);
	if (parse_and_display_reply(reply_buff) != 0)
	{
		ft_printf("GET command aborted.\n");
		close_data_connection(&dt);
		close(fd);
		return ;
	}
	if (get_file_from_server(dt.client_sock, fd) == FAILURE)
		ft_printf("GET command aborted.\n");
	close_data_connection(&dt);
	close(fd);
	parse_and_display_reply(reply_buff);
}

void			get_cmd(char *input)
{
	t_dt_socks	dt;
	int			fd;

	if (has_one_or_two_args(input) == FALSE)
	{
		ft_printf("%s\n", ARG_NB_ERR);
		ft_printf("Usage: %s\n", GET_USAGE);
		return ;
	}
	if ((fd = get_fd(input)) == -1)
	{
		ft_printf("GET command aborted.\n");
		return ;
	}
	if (etablish_data_connection(&dt) == FAILURE)
	{
		close_data_connection(&dt);
		ft_printf("GET command aborted.\n");
		return ;
	}
	manipulate_file(dt, input, fd);
}
