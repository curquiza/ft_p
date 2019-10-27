#include "client.h"

void	mode_cmd(char *input)
{
	if (has_no_arg(input) == FALSE)
	{
		ft_printf("%s\n", ARG_NB_ERR);
		ft_printf("Usage: %s\n", MODE_USAGE);
		return ;
	}
	ft_printf("Current mode: %s\n",
		(g_client.mode == ACTIVE ? "ACTIVE" : "PASSIVE"));
}
