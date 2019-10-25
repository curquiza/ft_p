#include "client.h"

t_cmd	g_cmd_tab[CMD_NB] =
{
	{ "help", &help_cmd, HELP_USAGE, HELP_DES },
	{ "cd", &cd_cmd, CD_USAGE, CD_DES },
	{ "pwd", &pwd_cmd, PWD_USAGE, PWD_DES },
	{ "ls", &ls_cmd, LS_USAGE, LS_DES },
	{ "mode", &mode_cmd, MODE_USAGE, MODE_DES },
	{ "pass", &pass_cmd, PASS_USAGE, PASS_DES },
	{ "quit", &quit_cmd, QUIT_USAGE, QUIT_DES },
};

static char	*get_cmd_name(char *cmd)
{
	int		i;
	char	*cmd_name;

	i = 0;
	while (cmd[i] && cmd[i] != ' ')
		i++;
	cmd_name = ft_strnew(i);
	if (cmd_name == NULL)
		ft_exit(MALLOC_ERR, 1);
	ft_memmove(cmd_name, cmd, i);
	return (cmd_name);
}

static void	exec_cmd(char *input)
{
	int		i;
	char	*cmd_name;

	i = 0;
	cmd_name = get_cmd_name(input);
	while (i < CMD_NB)
	{
		if (ft_strcmp(cmd_name, g_cmd_tab[i].name) == 0)
		{
			g_cmd_tab[i].f(input);
			free(cmd_name);
			return ;
		}
		i++;
	}
	free(cmd_name);
	ft_dprintf(2, "%s\n", UNKNOWN_CMD_ERR);
}

static void	display_prompt(void)
{
	ft_printf(B_PINK"curqui_ftp "DEF);
	if (g_current_path != NULL)
		ft_printf(B_GREEN"%s "DEF, g_current_path);
	ft_printf(B_PINK"$> "DEF);
}

t_ex_ret	communicate_with_server(void)
{
	char	*input;
	int		ret;

	input = NULL;
	g_current_path = ft_strdup("/");
	while (g_run == TRUE)
	{
		display_prompt();
		ret = get_next_line(0, &input);
		if (ret == -1)
		{
			free(g_current_path);
			return (ft_ret_err(READ_CMD_ERR));
		}
		else if (ret == 0)
		{
			ft_putchar('\n');
			quit_cmd("quit");
		}
		else
			exec_cmd(input);
		free(input);
	}
	return (SUCCESS);
}
