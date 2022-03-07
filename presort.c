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

int	move_to_top(int index, int stack_size)
{
	printf("index: %i, size: %i\n", index, stack_size);
	if (index > stack_size / 2)
		index = (stack_size - index) * -1;
	return (index);
}

void face_chunk(t_node *node, t_list *chunks, int stack_size)
{
	t_chunk *chunk;

	while (chunks)
	{
		chunk = (t_chunk *)chunks->content;
		//printf("face chunk in\n");
		if (node->val >= chunk->min && node->val <= chunk->max)
			break ;
		node->move_b += chunk->size;
		chunks = chunks->next;
	}
	if (node->move_b > stack_size / 2)
		node->move_b = (stack_size - node->move_b) * -1;
	if (node->move_b < 0)
		node->score += node->move_b * -1;
	else
		node->score += node->move_b;
	//printf("face chunk end\n");
}

void	get_scores(t_stacks *stacks, t_list *chunks)
{
	int 	i;
	t_node 	*node;

	node = stacks->a;
	//printf("node: %p\n", node->next);

	i = -1;
	while (++i < stacks->size_a)
	{
		if (node->score == 9999)
		{
			node = node->next;
			continue ;
		}
		//printf("score loop\n");
		node->move_a = move_to_top(i, stacks->size_a);
		if (node->move_a < 0)
			node->score += node->move_a * -1;
		else
			node->score += node->move_a;
		//printf("face chunk b4\n");
		face_chunk(node, chunks, stacks->size_b);
		//printf("face chunk after\n");
		//printf("curr val: %i\n", node->val);
		node = node->next;
		//printf("node: %p\n", node);
	}
}

void	print_scores(t_stacks *stacks)
{
	t_node	*node;

	node = stacks->a;
	while (node)
	{
		printf("%i\tscore: %i\tmove a: %i\tmove b: %i\n", node->val, node->score, node->move_a, node->move_b);
		node = node->next;
	}
}

void	presort(t_stacks **stacks)
{
	t_list	*chunks;
	int 	nb_chunks;
	int 	chunk_size;
	int 	last_chunk_size;

	printf("node: %p\n", (*stacks)->a->next);
	nb_chunks = 4;
	chunk_size = (*stacks)->size_a / nb_chunks;
	last_chunk_size = (*stacks)->size_a % chunk_size;
	if (last_chunk_size) {
		nb_chunks++;
	}
	chunks = init_chunks(chunk_size, nb_chunks, last_chunk_size);
	print_chunks(chunks);
	get_scores(*stacks, chunks);
	print_scores(*stacks);
}