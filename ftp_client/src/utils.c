#include "client.h"

void	usage(char *prgm)
{
	ft_dprintf(2, "Usage: %s: ./client [-6] <address> <port>\n", prgm);
	ft_dprintf(2, "  -6 : IPv6\n");
}

t_bool	has_no_arg(char *input)
{
	char	**args_tab;

	if (!input)
		return (FALSE);
	args_tab = ft_strsplit(input, ' ');
	if (!args_tab || ft_tablen(args_tab) != 1)
		return (FALSE);
	return (TRUE);
}

t_bool	has_only_one_arg(char *input)
{
	char	**args_tab;

	if (!input)
		return (FALSE);
	args_tab = ft_strsplit(input, ' ');
	if (!args_tab || ft_tablen(args_tab) != 2)
		return (FALSE);
	return (TRUE);
}
