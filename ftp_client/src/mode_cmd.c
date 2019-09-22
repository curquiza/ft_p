#include "client.h"

void		mode_cmd(char *input)
{
	if (has_no_arg(input) == FALSE)
	{
		ft_dprintf(2, "%s\n", ARG_NB_ERR);
		ft_dprintf(2, "Usage: %s\n", MODE_USAGE);
		return ;
	}
	ft_printf("Current mode: %s\n", (g_mode == ACTIVE ? "ACTIVE" : "PASSIVE"));
}
