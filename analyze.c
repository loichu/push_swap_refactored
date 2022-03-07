//
// Created by loichu on 07.03.22.
//

#include "push_swap.h"
#include <stdio.h>

t_nodalyze *new_node(int val, int ini)
{
	t_nodalyze *r;

	r = (t_nodalyze *)malloc(sizeof(t_nodalyze));
	if (!r)
		return (NULL);
	r->val = val;
	r->ini = ini;
	return (r);
}

void	ins_node(t_list **lst, t_list *new, t_list *prev, t_list *curr)
{
	if (!prev)
		*lst = new;
	else
		prev->next = new;
	new->next = curr;
}

void	lstadd_sort(t_list **lst, t_nodalyze *node)
{
	t_nodalyze 	*curr_node;
	t_list		*curr;
	t_list		*prev;
	t_list		*new;

	curr = *lst;
	new = ft_lstnew(node);
	prev = NULL;
	while (curr)
	{
		curr_node = (t_nodalyze *)curr->content;
		if (node->val == curr_node->val)
			return raise_error(1);
		else if (node->val < curr_node->val)
			return ins_node(lst, new, prev, curr);
		prev = curr;
		curr = curr->next;
	}
	prev->next = new;
}

void	print_res(t_list *init, t_list *sort)
{
	while (init && sort) {
		printf("%i\t%i\n", ((t_nodalyze *) init->content)->val, ((t_nodalyze *) sort->content)->val);
		init = init->next;
		sort = sort->next;
	}
}

void	print_single(t_list *list)
{
	while (list) {
		printf("%i\n", ((t_nodalyze *) list->content)->val);
		list = list->next;
	}
}

void	replace_values(t_list *sorted)
{
	static int index = 0;

	((t_nodalyze *) sorted->content)->val = index++;
	if (sorted->next)
		replace_values(sorted->next);
	free(sorted);
}

t_list *analyze(char **input, int size)
{
	int			i;
	t_list 		*initial;
	t_list 		*sorted;
	t_nodalyze 	*node;

	i = 0;
	node = new_node(ft_atoi(input[i]), i);
	initial = ft_lstnew(node);
	sorted = ft_lstnew(node);
	while (++i < size)
	{
		node = new_node(ft_atoi(input[i]), i);
		ft_lstadd_back(&initial, ft_lstnew(node));
		lstadd_sort(&sorted, node);
	}
	print_res(initial, sorted);
	replace_values(sorted);
	print_single(initial);
	return (initial);
}