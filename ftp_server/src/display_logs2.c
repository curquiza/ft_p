#include "server.h"

void	log_data_sent_into_dt_channel(t_user *user, char *s)
{
	char	*tmp;

	tmp = ft_strjoin(": ", s);
	if (user->mode == PASSIVE)
		print_data_output("--> Sent through DT channel on port",
			user->dt_port, tmp, NULL);
	else
		print_data_output("--> Sent through DT channel on user's port",
			user->dt_port, tmp, NULL);
	free(tmp);
}

void	log_data_received_from_dt_channel(t_user *user, char *s)
{
	char	*tmp;

	tmp = ft_strjoin(": ", s);
	if (user->mode == PASSIVE)
		print_data_output("<-- Received from DT channel on port",
			user->dt_port, tmp, NULL);
	else
		print_data_output("<-- Received from DT channel on user's port",
			user->dt_port, tmp, NULL);
	free(tmp);
}
