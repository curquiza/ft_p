#include "client.h"

void		ls_cmd(char *input)
{
	int		dt_client_sock;

	if (has_zero_or_one_arg(input) == FALSE)
	{
		ft_printf("%s\n", ARG_NB_ERR);
		ft_printf("Usage: %s\n", LS_USAGE);
		return ;
	}
	if ((dt_client_sock = etablish_data_connection()) == -1)
	{
		ft_printf("LS command failed.\n");
		return ;
	}
	ft_printf("READ AND DISPLAY LS !!\n");
}
