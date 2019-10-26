#include "client.h"

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

void		pwd_cmd(char *input)
{
	char	reply_buff[REPLY_MAX_SIZE];

	if (has_no_arg(input) == FALSE)
	{
		ft_printf("%s\n", ARG_NB_ERR);
		ft_printf("Usage: %s\n", PWD_USAGE);
		return ;
	}
	send_to_server("PWD");
	if (parse_and_display_reply(reply_buff) == 0)
		get_new_path(reply_buff);
}
