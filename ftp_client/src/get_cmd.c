#include "client.h"

static int get_fd(char *input)
{
	int		fd;
	char	**args;

	args = ft_strsplit(input, ' ');
	if (ft_tablen(args) == 2)
		fd = open(args[1], O_RDONLY);
	else
		fd = open(args[2], O_RDONLY);
	ft_tabdel(&args);
	if (fd == -1)
		return (print_and_return_neg(CREATE_FILE_ERR));
	return (fd);
}

// static void manipulate_file(t_dt_socks dt, char *input, int fd)
// {
// }

void		get_cmd(char *input)
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
	// manipulate_file(dt, input, fd);
}
