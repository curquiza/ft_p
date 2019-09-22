#include "client.h"

void		help_cmd(char *input)
{
	if (has_no_arg(input) == FALSE)
	{
		ft_dprintf(2, "%s\n", ARG_NB_ERR);
		ft_dprintf(2, "Usage: help\n");
		return ;
	}
}
