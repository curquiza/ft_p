#include "client.h"

void	usage(char *prgm)
{
	ft_dprintf(2, "Usage: %s: ./client [-6] <address> <port>\n", prgm);
	ft_dprintf(2, "  -6 : IPv6\n");
	ft_dprintf(2, "  -a : force active mode\n");
}

t_ex_ret		print_and_return_failure(char *str)
{
	ft_printf("%s\n", str);
	return (FAILURE);
}

int				print_and_return_neg(char *str)
{
	ft_printf("%s\n", str);
	return (-1);
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

t_bool	has_zero_or_one_arg(char *input)
{
	return (has_no_arg(input) || has_only_one_arg(input));
}
