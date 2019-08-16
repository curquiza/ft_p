#include "server.h"

void		exec_get_cmd(t_user *user, char *cmd)
{
	struct stat		stat_struct;
	int				size;
	t_byte			*ptr;

	(void)cmd;
	int fd = open("test/input/package-lock.json", O_RDONLY);
	fstat(fd, &stat_struct);
	size = stat_struct.st_size;
	ptr = NULL;
	ptr = mmap(ptr, size, PROT_READ, MAP_PRIVATE, fd, 0);
	send(user->ctrl_client_sock, ptr, size, 0);
	close(fd);
}
