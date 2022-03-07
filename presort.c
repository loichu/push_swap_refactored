#include "push_swap.h"

typedef struct	s_chunk
{
	int max_size;
	int size;
	int min;
	int max;
	//int cursor;
}	t_chunk;

t_list *init_chunks(int chunk_size, int nb_chunks, int last_chunk_size)
{
	t_chunk *chunk;
	t_list 	*chunks;
	int 	i;

	chunks = NULL;
	i = 0;
	while (i++ < nb_chunks)
	{
		printf("Create chunk #%i\n", i);
		chunk = (t_chunk *)malloc(sizeof(t_chunk));
		chunk->min = (i - 1) * chunk_size;
		if (nb_chunks == i && last_chunk_size) {
			chunk_size = last_chunk_size;
		}
		chunk->max = chunk->min + chunk_size - 1;
		chunk->max_size = chunk_size;
		chunk->size = 0;
		printf("Created chunk #%i\n", i);
		ft_lstadd_back(&chunks, ft_lstnew(chunk));
	}
	//chunk->cursor = 0;
	return (chunks);
}

void	print_chunks(t_list *chunks)
{
	t_chunk		*chunk;
	static int	i;

	i = 0;
	chunk = (t_chunk *)chunks->content;
	while (chunk)
	{
		printf("Chunk #%i: %i → %i\n", ++i, chunk->min, chunk->max);
		if ((chunks = chunks->next))
			chunk = (t_chunk *)chunks->content;
		else
			chunk = NULL;
	}
}

void	presort(t_stacks **stacks)
{
	t_list	*chunks;
	int 	nb_chunks;
	int 	chunk_size;
	int 	last_chunk_size;

	nb_chunks = 4;
	chunk_size = (*stacks)->size_a / nb_chunks;
	last_chunk_size = (*stacks)->size_a % chunk_size;
	if (last_chunk_size) {
		nb_chunks++;
	}
	chunks = init_chunks(chunk_size, nb_chunks, last_chunk_size);
	print_chunks(chunks);
}