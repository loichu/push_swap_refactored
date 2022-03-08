#include "push_swap.h"

void	push(t_node **to, t_node **from)
{
	t_node *tmp;

	if (!*from)
		return ;
	tmp = (*from)->next;
	(*from)->next = *to;
	*to = *from;
	*from = tmp;
}

void	p(char stack, t_stacks **stacks)
{
	if (stack == 'a')
	{
		push(&(*stacks)->a, &(*stacks)->b);
		(*stacks)->size_a++;
		(*stacks)->size_b--;
	}
	else if (stack == 'b')
	{
		push(&(*stacks)->b, &(*stacks)->a);
		(*stacks)->size_b++;
		(*stacks)->size_a--;
	}
	ft_putchar_fd('p', 1);
	ft_putchar_fd(stack, 1);
	ft_putchar_fd('\n', 1);
}

void	p_chunk(t_list **chunks, t_stacks **stacks)
{
	t_node	*node;
	t_chunk *chunk;

	chunk = (t_chunk *)(*chunks)->content;
	chunk->size++;
	node = (*stacks)->a;
	(*stacks)->a = node->next;
	if (node->move_b < 0)
	{
		node_addback(&(chunk->nodes), node);
		rotate_chunks(chunks);
	}
	else
	{
		node_addfront(&(chunk->nodes), node);
	}
	(*stacks)->size_b++;
	(*stacks)->size_a--;
	ft_putstr_fd("pb\n", 1);
}