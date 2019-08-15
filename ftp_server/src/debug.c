#include "server.h"

void	print_verbose_ss(char *s1, char *s2)
{
	if (opt_is_activated('v'))
	{
		ft_printf("-> %s %s\n", s1, s2);
	}
}

void	print_verbose_sis(char *s1, int i, char *s2)
{
	if (opt_is_activated('v'))
	{
		ft_printf("-> %s %d %s\n", s1, i, s2);
	}
}

void	print_verbose_siss(char *s1, int i, char *s2, char *s3)
{
	if (opt_is_activated('v'))
	{
		ft_printf("-> %s %d %s %s\n", s1, i, s2, s3);
	}
}
