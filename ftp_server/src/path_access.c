#include "server.h"

char	*get_root_path(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
		ft_dprintf(2, ROOT_PATH_ERR);
	return (path);
}
