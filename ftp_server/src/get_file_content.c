#include "server.h"

static void	clean_list(t_chunk **list)
{
	t_chunk	*tmp;
	t_chunk	*c;

	c = *list;
	while (c)
	{
		tmp = c;
		c = c->next;
		free(tmp);
	}
}

static void	list_push_back(t_chunk **alst, t_chunk *new, t_chunk **end)
{
	if (alst == NULL || new == NULL)
		return ;
	else if (*alst == NULL)
	{
		*alst = new;
		*end = new;
	}
	else
	{
		new->next = NULL;
		(*end)->next = new;
		*end = new;
	}
}

static t_chunk	*new_chunk(int size, char *content)
{
	t_chunk		*new_chunk;

	if (!(new_chunk = (t_chunk*)ft_memalloc(sizeof(*new_chunk))))
		ft_exit(MALLOC_ERR, 1);
	new_chunk->size = size;
	ft_memmove(new_chunk->content, content, size);
	new_chunk->next = NULL;
	return (new_chunk);
}

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
