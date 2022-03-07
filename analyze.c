//
// Created by loichu on 07.03.22.
//

#include "push_swap.h"
#include <stdio.h>

t_node *new_node(int val)
{
	t_node *r;

	r = (t_node *)malloc(sizeof(t_node));
	if (!r)
		return (NULL);
	r->val = val;
	r->next = NULL;
	return (r);
}

void	node_addback(t_node **list, t_node *new)
{
	t_node	*iter;

	if (!list)
		return ;
	if (!*list)
	{
		*list = new;
		return ;
	}
	iter = *list;
	while (iter->next)
		iter = iter->next;
	iter->next = new;
}

void	ins_node(t_list **lst, t_list *new, t_list *prev, t_list *curr)
{
	if (!prev)
		*lst = new;
	else
		prev->next = new;
	new->next = curr;
}

void	lstadd_sort(t_list **lst, t_node *node)
{
	t_node 	*curr_node;
	t_list	*curr;
	t_list	*prev;
	t_list	*new;

	curr = *lst;
	new = ft_lstnew(node);
	prev = NULL;
	while (curr)
	{
		curr_node = (t_node *)curr->content;
		if (node->val == curr_node->val)
			return raise_error(1);
		else if (node->val < curr_node->val)
			return ins_node(lst, new, prev, curr);
		prev = curr;
		curr = curr->next;
	}
	prev->next = new;
}

void	print_res(t_node *init, t_list *sort)
{
	while (init && sort) {
		printf("%i\t%i\n", init->val, ((t_node *) sort->content)->val);
		init = init->next;
		sort = sort->next;
	}
}

void	print_nodes(t_node *node)
{
	while (node) {
		printf("%i\n", node->val);
		node = node->next;
	}
}

void	replace_values(t_list *sorted)
{
	static int index = 0;

	((t_node *) sorted->content)->val = index++;
	if (sorted->next)
		replace_values(sorted->next);
	free(sorted);
}

t_node *analyze(char **input, int size)
{
	int		i;
	t_node	*initial;
	t_list	*sorted;
	t_node	*node;

	i = 0;
	node = new_node(ft_atoi(input[i]));
	initial = node;
	sorted = ft_lstnew(node);
	while (++i < size)
	{
		node = new_node(ft_atoi(input[i]));
		node_addback(&initial, node);
		lstadd_sort(&sorted, node);
	}
	print_res(initial, sorted);
	replace_values(sorted);
	print_nodes(initial);
	return (initial);
}