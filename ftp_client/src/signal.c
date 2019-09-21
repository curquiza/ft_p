#include "client.h"

void	sigint_handler(int sig)
{
	(void)sig;
	ft_putchar('\n');
	quit_cmd(NULL);
	exit(SUCCESS);
}
