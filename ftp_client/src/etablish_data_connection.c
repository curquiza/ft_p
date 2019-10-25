#include "client.h"

static void	ask_for_data_connection(void)
{
	char	*line_to_send;

	if (g_mode == PASSIVE)
		line_to_send = ft_strdup(g_addr_family == AF_INET6 ? "EPSV" : "PASV");
	else
		line_to_send = NULL;
	send_to_server(line_to_send);
	free(line_to_send);
}

int		etablish_data_connection(void)
{
	ask_for_data_connection();
	if (g_mode == PASSIVE)
		return (etablish_data_connection_passive());
	// return(etablish_data_connection_active())
	return (-1);
}
