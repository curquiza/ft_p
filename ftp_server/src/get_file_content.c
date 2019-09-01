#include "server.h"

static char		*list_to_char(t_chunk *chunks, int tot_size)
{
	char	*rslt;
	int		i;

	rslt = ft_memalloc(tot_size);
	if (rslt == NULL)
		ft_exit(MALLOC_ERR, 1);
	i = 0;
	while(chunks)
	{
		ft_memmove(rslt + i, chunks->content, chunks->size);
		i += chunks->size;
		chunks = chunks->next;
	}
	return (rslt);
}

char		*get_file_content(t_user *user, int *size)
{
	char		buff[READ_BUFF];
	t_chunk		*new;
	t_chunk		*chunks;
	t_chunk		*end;
	int			total_size;
	int			ret;
	char		*file_content;

	chunks = NULL;
	end = NULL;
	total_size = 0;
	while ((ret = recv(user->dt_client_sock, buff, READ_BUFF, 0)) > 0)
	{
		new = new_chunk(ret, buff);
		list_push_back(&chunks, new, &end);
		total_size += ret;
	}
	*size = total_size;
	if (ret == -1)
	{
		clean_list(&chunks);
		*size = 0;
		return (NULL);
	}
	file_content = list_to_char(chunks, total_size);
	clean_list(&chunks);
	return (file_content);
}
