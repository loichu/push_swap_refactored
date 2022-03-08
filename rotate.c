#include "push_swap.h"

void	rotate(t_node **stk)
{
	t_node *tmp;

	if (!*stk)
		return ;
	tmp = *stk;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = *stk;
	*stk = (*stk)->next;
	tmp->next->next = NULL;
}

void	reverse(t_node **stk)
{
	t_node *tmp;
	t_node *prev;

	if (!(*stk && (*stk)->next))
		return ;
	prev = *stk;
	tmp = (*stk)->next;
	while (tmp->next)
	{
		prev = prev->next;
		tmp = tmp->next;
	}
	prev->next = NULL;
	tmp->next = *stk;
	*stk = tmp;
}

//void	r_chunk(t_chunk **chunks, t_stacks **stacks)
//{
//	ft_putstr_fd("rb\n", 1);
//}

void	r(char *cmd, t_stacks **stacks)
{
	ft_putstr_fd(cmd, 1);
	ft_putchar_fd('\n', 1);
	if (*cmd == 'a')
		rotate(&(*stacks)->a);
	else if (*cmd == 'b')
		rotate(&(*stacks)->b);
	else if (*cmd++ == 'r')
	{
		if (*cmd == 'a')
			reverse(&(*stacks)->a);
		else if (*cmd == 'b')
			reverse(&(*stacks)->b);
		else if (*cmd == 'r')
		{
			reverse(&(*stacks)->a);
			reverse(&(*stacks)->b);
		}
		else if (*cmd == '\0')
		{
			rotate(&(*stacks)->a);
			rotate(&(*stacks)->b);
		}
	}
}