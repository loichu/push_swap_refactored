//
// Created by loichu on 08.03.22.
//
#include "push_swap.h"

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

//void	rotate_chunks(t_list **chunks)
//{
//	t_chunk	*first_chunk;
//	t_node	*node_iter;
//
//	first_chunk = (t_chunk *)(*chunks)->next->content;
//	node_iter = (t_node *)first_chunk->nodes;
//	while (node_iter)
//	{
//		ft_putstr_fd("rb")
//	}
//}

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