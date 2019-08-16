# include "server.h"

void		list_cmd(t_user *user)
{
	char	*args[3] = { "/bin/ls", "-l", NULL };
	pid_t	pid;

	if (user->dt_client_sock == -1)
	{
		send_oneline_reply_to_user(user->ctrl_client_sock, user->num, RES_426);
		return ;
	}
	if ((pid = fork()) < 0)
	{
		send_oneline_reply_to_user(user->ctrl_client_sock, user->num, RES_451);
		return ;
	}
	if (pid == 0)
	{
		send_oneline_reply_to_user(user->ctrl_client_sock, user->num, RES_125);
		dup2(user->dt_client_sock, STDOUT_FILENO);
		execv(args[0], args);
		ft_dprintf(STDERR_FILENO, "Error during execv\n");
		exit(1);
	}
	else
	{
		wait4(0, NULL, 0, NULL);
		print_data_output("--> Sent in DT channel on port", user->dt_port, ": * LS output *", NULL);
		close_user_data_channel(user);		// necessaire de close ??
		send_oneline_reply_to_user(user->ctrl_client_sock, user->num, RES_226);
	}
}