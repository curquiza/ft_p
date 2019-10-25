#include "client.h"

void		ls_cmd(char *input)
{
	int		dt_client_sock;

	(void)input;
	// check arg number
	if ((dt_client_sock = etablish_data_connection()) == -1)
	{
		ft_printf("LS command failed.\n");
		return ;
	}
	ft_printf("READ AND DISPLAY LS !!\n");
}
