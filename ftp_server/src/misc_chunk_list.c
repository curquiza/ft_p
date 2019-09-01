#include "server.h"

void	clean_list(t_chunk **list)
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

void	list_push_back(t_chunk **alst, t_chunk *new, t_chunk **end)
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

t_chunk	*new_chunk(int size, char *content)
{
	t_chunk		*new_chunk;

	if (!(new_chunk = (t_chunk*)ft_memalloc(sizeof(*new_chunk))))
		ft_exit(MALLOC_ERR, 1);
	new_chunk->size = size;
	ft_memmove(new_chunk->content, content, size);
	new_chunk->next = NULL;
	return (new_chunk);
}
