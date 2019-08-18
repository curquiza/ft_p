# include "server.h"

static char		*get_ls_arg(char *cmd)
{
	char	**args;
	int		size;
	char	*rslt;

	args = ft_strsplit(cmd, ' ');
	if (!args)
		ft_exit(MALLOC_ERR, 1);
	size = ft_tablen(args);
	rslt = NULL;
	if (size == 1)
		rslt = ft_strdup(".");
	else if (size == 2 && args[1][0] != '-')
		rslt = ft_strdup(args[1]);
	ft_tabdel(&args);
	return (rslt);
	// /!\ verifier que ca ne remonte pas loin dans l'arborescence et renvoyer le bon argument
}

static void	child_process(t_user *user, char *ls_arg)
{
	char	*args[4];

	args[0] = "/bin/ls";
	args[1] = "-l";
	args[2] = ls_arg;
	args[3] = NULL;
	send_oneline_reply_to_user(user, RES_125);
	dup2(user->dt_client_sock, STDOUT_FILENO);
	execv(args[0], args);
	free(ls_arg);
	exit(1);
}

static void	parent_process(t_user *user)
{
	int		status;

	status = 0;
	wait4(0, &status, 0, NULL);
	if (status == 256)
	{
		print_data_output(NULL, 0, "Error during ls execution", NULL);
		send_oneline_reply_to_user(user, RES_451);
		close_user_data_channel(user);
		return ;
	}
	if (user->mode == PASSIVE)
		print_data_output("--> Sent through DT channel on port",
			user->dt_port, ": * LS output *", NULL);
	else
		print_data_output("--> Sent through DT channel on user's port",
			user->dt_port, ": * LS output *", NULL);
	close_user_data_channel(user);
	send_oneline_reply_to_user(user, RES_226);
}

void		exec_list_cmd(t_user *user, char *cmd)
{
	char	*ls_arg;
	pid_t	pid;

	if (!(ls_arg = get_ls_arg(cmd)))
	{
		send_oneline_reply_to_user(user, RES_501);
		return ;
	}
	if (is_dt_channel_open(user) == FALSE)
	{
		free(ls_arg);
		send_oneline_reply_to_user(user, RES_426);
		return ;
	}
	if ((pid = fork()) < 0)
	{
		free(ls_arg);
		send_oneline_reply_to_user(user, RES_451);
		return ;
	}
	if (pid == 0)
		child_process(user, ls_arg);
	else
		parent_process(user);
	free(ls_arg);
}
