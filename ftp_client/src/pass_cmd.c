#include "client.h"

void		pass_cmd(char *input)
{
	if (has_no_arg(input) == FALSE)
	{
		ft_printf("%s\n", ARG_NB_ERR);
		ft_printf("Usage: %s\n", PASS_USAGE);
		return ;
	}
	if (g_mode == ACTIVE)
	{
		g_mode = PASSIVE;
		ft_printf("Passive mode ON\n");
	}
	else
	{
		g_mode = ACTIVE;
		ft_printf("Passive mode OFF\n");
	}
}
