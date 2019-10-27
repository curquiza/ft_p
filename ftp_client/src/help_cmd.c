#include "client.h"

void		help_cmd(char *input)
{
	int		i;

	if (has_no_arg(input) == FALSE)
	{
		ft_printf("%s\n", ARG_NB_ERR);
		ft_printf("Usage: %s\n", HELP_USAGE);
		return ;
	}
	ft_printf("Commands:\n");
	i = 0;
	while (i < CMD_NB)
	{
		ft_printf("   - %-35s %s\n", g_cmd_tab[i].usage,
			g_cmd_tab[i].description);
		i++;
	}
}
