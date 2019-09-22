#include "client.h"

static void	send_cwd_cmd_to_server(char *input)
{
	char	**args;
	char	*cmd;

	args = ft_strsplit(input, ' ');
	cmd = ft_strjoin("CWD ", args[1]);
	send_to_server(cmd);
	ft_tabdel(&args);
	free(cmd);
}

void		cd_cmd(char *input)
{
	if (has_only_one_arg(input) == FALSE)
	{
		ft_dprintf(2, "%s\n", ARG_NB_ERR);
		ft_dprintf(2, "Usage: cd <path>\n");
		return ;
	}
	send_cwd_cmd_to_server(input);
	if (parse_and_display_reply() == 0)
	{
		send_to_server("PWD");
		parse_and_display_reply();
	}
}
