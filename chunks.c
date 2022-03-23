//
// Created by loichu on 08.03.22.
//
#include "push_swap.h"

t_list	*init_chunks(int chunk_size, int nb_chunks, int last_chunk_size)
{
	t_chunk *chunk;
	t_list 	*chunks;
	int 	i;

	chunks = NULL;
	i = 0;
	while (i++ < nb_chunks)
	{
		chunk = (t_chunk *)malloc(sizeof(t_chunk));
		chunk->min = (i - 1) * chunk_size;
		if (nb_chunks == i && last_chunk_size) {
			chunk_size = last_chunk_size;
		}
		chunk->max = chunk->min + chunk_size - 1;
		chunk->max_size = chunk_size;
		chunk->size = 0;
		ft_lstadd_back(&chunks, ft_lstnew(chunk));
	}
	reverse_rotate_chunks(&chunks);
	return (chunks);
}

void	rotate_chunks(t_list **chunks)
{
	t_list	*chunk_iter;

	chunk_iter = *chunks;
	while (chunk_iter->next)
		chunk_iter = chunk_iter->next;
	chunk_iter->next = *chunks;
	*chunks = (*chunks)->next;
	chunk_iter->next->next = NULL;
}

void	reverse_rotate_chunks(t_list **chunks)
{
	t_list *tmp;
	t_list *prev;

	if (!(*chunks && (*chunks)->next))
		return ;
	prev = *chunks;
	tmp = (*chunks)->next;
	while (tmp->next)
	{
		prev = prev->next;
		tmp = tmp->next;
	}
	prev->next = NULL;
	tmp->next = *chunks;
	*chunks = tmp;
}

bool	is_in_chunk(t_node *node, t_chunk *chunk)
{
	if (node->val >= chunk->min && node->val <= chunk->max)
		return (true);
	return (false);
}

int	move_to_chunk(t_node *node, t_list *chunks, int stack_size)
{
	t_chunk	*first_chunk;
	t_chunk	*last_chunk;
	int 	move;

	move = 0;
	while (chunks->next)
	{
		first_chunk = (t_chunk *)chunks->next->content;
		last_chunk = (t_chunk *)chunks->content;
		if (is_in_chunk(node, first_chunk) || is_in_chunk(node, last_chunk))
			break ;
		move += first_chunk->size;
		chunks = chunks->next;
	}
	if (move > stack_size / 2)
		move = (stack_size - move) * -1;
	return (move);
}