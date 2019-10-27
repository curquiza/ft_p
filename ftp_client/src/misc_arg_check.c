#include "client.h"

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
