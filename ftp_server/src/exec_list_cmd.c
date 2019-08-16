# include "server.h"

void		exec_list_cmd(t_user *user, char *cmd)
{
	char	*args[3] = { "/bin/ls", "-l", NULL };
	// char	*cmd_args;
	pid_t	pid;

	(void)cmd; // check si good parametre
	if (is_dt_channel_open(user) == FALSE)
	{
		send_oneline_reply_to_user(user, RES_426);
		return ;
	}
	if ((pid = fork()) < 0)
	{
		send_oneline_reply_to_user(user, RES_451);
		return ;
	}
	if (pid == 0)
	{
		send_oneline_reply_to_user(user, RES_125);
		dup2(user->dt_client_sock, STDOUT_FILENO);
		execv(args[0], args);
		ft_dprintf(STDERR_FILENO, "Error during execv\n");
		exit(1);
	}
	else
	{
		wait4(0, NULL, 0, NULL);
		if (user->mode == PASSIVE)
			print_data_output("--> Sent through DT channel on port", user->dt_port, ": * LS output *", NULL);
		else
			print_data_output("--> Sent through DT channel on user's port", user->dt_port, ": * LS output *", NULL);
		close_user_data_channel(user);		// necessaire de close ??
		send_oneline_reply_to_user(user, RES_226);
	}
}
