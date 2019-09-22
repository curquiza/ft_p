#include "client.h"

void		help_cmd(char *input)
{
	if (has_no_arg(input) == FALSE)
	{
		ft_dprintf(2, "%s\n", ARG_NB_ERR);
		ft_dprintf(2, "Usage: %s\n", HELP_USAGE);
		return ;
	}
	ft_printf("Commands:\n");
	ft_printf("   - %-35s %s\n", HELP_USAGE, HELP_DES);
	ft_printf("   - %-35s %s\n", PWD_USAGE, PWD_DES);
	ft_printf("   - %-35s %s\n", CD_USAGE, CD_DES);
	ft_printf("   - %-35s %s\n", LS_USAGE, LS_DES);
	ft_printf("   - %-35s %s\n", GET_USAGE, GET_DES);
	ft_printf("   - %-35s %s\n", PUT_USAGE, PUT_DES);
	ft_printf("   - %-35s %s\n", QUIT_USAGE, QUIT_DES);
}
