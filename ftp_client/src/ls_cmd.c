#include "client.h"

void		ls_cmd(char *input)
{
	int		dt_client_sock;

	if (has_zero_or_one_arg(input) == FALSE)
	{
		ft_dprintf(2, "%s\n", ARG_NB_ERR);
		ft_dprintf(2, "Usage: %s\n", LS_USAGE);
		return ;
	}
	if ((dt_client_sock = etablish_data_connection()) == -1)
	{
		ft_printf("LS command failed.\n");
		return ;
	}
	ft_printf("READ AND DISPLAY LS !!\n");
}
