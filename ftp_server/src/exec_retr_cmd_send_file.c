#include "server.h"

void		send_file(t_user *user, t_byte *ptr, int size)
{
	int				total_send;
	int				ret;

	total_send = 0;
	ret = 0;
	while (total_send < size)
	{
		ret = send(user->dt_client_sock, ptr, size - total_send, 0);
		if (ret == -1)
			break;
		total_send += ret;
	}
	if (ret == -1)
		send_oneline_reply_to_user(user, RES_451);
	else
	{
		send_oneline_reply_to_user(user, RES_226);
		log_data_sent_into_dt_channel(user, "* FILE *");
	}
}
