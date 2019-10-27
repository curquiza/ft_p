#include "server.h"

static char	*get_cmd_name(char *cmd)
{
	int		i;
	char	*cmd_name;

	i = 0;
	while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\n' && cmd[i] != '\r')
		i++;
	cmd_name = ft_strnew(i);
	if (cmd_name == NULL)
		ft_exit(MALLOC_ERR, 1);
	ft_memmove(cmd_name, cmd, i);
	return (cmd_name);
}

static void	exec_cmd(t_user *user, char *cmd)
{
	int		i;
	char	*cmd_name;

	i = 0;
	cmd_name = get_cmd_name(cmd);
	while (i < CMD_NB)
	{
		if (ft_strcmp(cmd_name, g_cmd_tab[i].name) == 0)
		{
			g_cmd_tab[i].f(user, cmd);
			free(cmd_name);
			return ;
		}
		i++;
	}
	free(cmd_name);
	send_oneline_reply_to_user(user, RES_500);
}

void		communicate_with_new_user(t_user *user)
{
	char	cmd[1024];
	int		len;

	send_oneline_reply_to_user(user, RES_220);
	while ((len = recv(user->ctrl_client_sock, &cmd, 1024, 0)) > 0)
	{
		if (len >= 2 && cmd[len - 2] == '\r')
			cmd[len - 2] = '\0';
		else if (len >= 1 && cmd[len - 1] == '\n')
			cmd[len - 1] = '\0';
		else
			cmd[len] = '\0';
		print_ctrl_output("<-- Received from Client", user->num, ":", cmd);
		if (ft_strcmp(cmd, "QUIT") == 0)
			break ;
		exec_cmd(user, cmd);
	}
}
