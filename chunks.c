//
// Created by loichu on 08.03.22.
//
#include "push_swap.h"

void	rotate_chunks(t_list **chunks)
{
	//t_chunk	*curr_chunk;
	t_list	*chunk_iter;

	//curr_chunk = (t_chunk *)(*chunks)->content;
	chunk_iter = *chunks;
	printf("loop\n");
	while (chunk_iter->next)
		chunk_iter = chunk_iter->next;
	printf("found last\n");
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