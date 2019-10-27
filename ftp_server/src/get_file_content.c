#include "server.h"

/*
** Creates chunk linked list and returns total size
** Returns -1 if failure
*/
static int	get_chunks_list(t_user *user, t_chunk **chunks)
{
	char		buff[READ_BUFF];
	t_chunk		*new;
	t_chunk		*end;
	int			ret;
	int			total_size;

	total_size = 0;
	while ((ret = recv(user->dt_client_sock, buff, READ_BUFF, 0)) > 0)
	{
		new = new_chunk(ret, buff);
		list_push_back(chunks, new, &end);
		total_size += ret;
	}
	if (ret == -1)
		return (-1);
	return (total_size);
}

static char	*list_to_char(t_chunk *chunks, int tot_size)
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

	t_chunk		*chunks;
	char		*file_content;

	chunks = NULL;
	*size = get_chunks_list(user, &chunks);
	if (*size == -1)
	{
		*size = 0;
		clean_list(&chunks);
		return (NULL);
	}
	file_content = list_to_char(chunks, *size);
	clean_list(&chunks);
	return (file_content);
}
