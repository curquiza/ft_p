#include "client.h"

int		etablish_data_connection(void)
{
	if (g_mode == PASSIVE)
		return (etablish_data_connection_passive());
	return(etablish_data_connection_active());
}
