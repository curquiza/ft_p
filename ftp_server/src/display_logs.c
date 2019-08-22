#include "server.h"

static void	print_output(char *s1, int i, char *s2, char *s3)
{
	if (s1 == NULL)
		ft_printf("%s\n", s2);
	else if (s2 == NULL)
		ft_printf("%s %d\n", s1, i);
	else if (s3 == NULL)
		ft_printf("%s %d %s\n", s1, i, s2);
	else
		ft_printf("%s %d %s %s\n", s1, i, s2, s3);
}

void	print_ctrl_output(char *s1, int i, char *s2, char *s3)
{
	ft_printf(B_YELLOW"[CTRL]  "DEF);
	print_output(s1, i, s2, s3);
}

void	print_data_output(char *s1, int i, char *s2, char *s3)
{
	ft_printf(B_BLUE"[DATA]  "DEF);
	print_output(s1, i, s2, s3);
}

void	print_debug_output(char *s1, int i, char *s2, char *s3)
{
	ft_printf("[INFO]  ");
	print_output(s1, i, s2, s3);
}
