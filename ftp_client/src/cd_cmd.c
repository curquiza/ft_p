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

static void	get_new_path(char *reply)
{
	char	**reply_tab;
	char	*new_path;

	free(g_current_path);
	g_current_path = NULL;
	if (!reply || !reply[0])
		return ;
	reply_tab = ft_strsplit(reply, ' ');
	if (!reply_tab || ft_tablen(reply_tab) < 2)
		return ;
	new_path = reply_tab[1];
	if (new_path[0] && new_path[0] == '"')
	{
		new_path[ft_strlen(new_path) - 1] = '\0';
		g_current_path = ft_strdup(new_path + 1);
	}
	else
		g_current_path = ft_strdup(new_path);
}

void		cd_cmd(char *input)
{
	char	reply_buff[REPLY_MAX_SIZE];

	if (has_only_one_arg(input) == FALSE)
	{
		ft_dprintf(2, "%s\n", ARG_NB_ERR);
		ft_dprintf(2, "Usage: cd <path>\n");
		return ;
	}
	send_cwd_cmd_to_server(input);
	if (parse_and_display_reply(reply_buff) == 0)
	{
		send_to_server("PWD");
		if (parse_and_display_reply(reply_buff) == 0)
			get_new_path(reply_buff);
	}
}
