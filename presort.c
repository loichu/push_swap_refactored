#include "push_swap.h"

int	move_to_top(int index, int stack_size)
{
	if (index > stack_size / 2)
		index = (stack_size - index) * -1;
	return (index);
}

int calc_score(t_node *node)
{
	if (node->move_a * node->move_b > 0)
		return (max(abs(node->move_a), abs(node->move_b)));
	return (abs(node->move_a) + abs(node->move_b));
}

void	get_scores(t_stacks *stacks, t_list *chunks)
{
	int 	i;
	t_node 	*node;

	node = stacks->a;
	i = -1;
	while (++i < stacks->size_a)
	{
		if (node->score == -1)
		{
			node = node->next;
			continue ;
		}
		node->move_a = move_to_top(i, stacks->size_a);
		node->move_b = move_to_chunk(node, chunks, stacks->size_b);
		node->score = calc_score(node);
		if (is_in_chunk(node, (t_chunk *)chunks->content))
			node->score++;
		node = node->next;
	}
}

void	exec_rotates(t_stacks **stacks, char stack, int moves)
{
	char	*cmd;
	int 	i;

	i = 0;
	cmd = (char *)malloc(3 * sizeof(char));
	if (moves < 0)
		cmd[i++] = 'r';
	cmd[i++] = stack;
	cmd[i] = '\0';
	moves = abs(moves);
	while (moves--)
		chunks_r(cmd, stacks);
}

void	exec_rotates_together(t_stacks **stacks, t_node *best_node)
{
	char	*cmd;
	int 	moves;

	moves = min(abs(best_node->move_a), abs(best_node->move_b));
	if (best_node->move_a > 0)
	{
		cmd = "r";
		best_node->move_a -= moves;
		best_node->move_b -= moves;
	}
	else
	{
		cmd = "rr";
		best_node->move_a += moves;
		best_node->move_b += moves;
	}
	while (moves--)
		chunks_r(cmd, stacks);
}

void	rotate_stacks(t_stacks **stacks, t_node *best_node)
{
	if (best_node->move_a * best_node->move_b > 0)
		exec_rotates_together(stacks, best_node);
	if (best_node->move_a)
		exec_rotates(stacks, 'a', best_node->move_a);
	if (best_node->move_b)
		exec_rotates(stacks, 'b', best_node->move_b);
}

void	make_moves(t_stacks **stacks, t_list **chunks)
{
	t_node	*best_node;
	t_chunk	*first_chunk;
	t_chunk	*last_chunk;

	best_node = get_best_node((*stacks)->a);
	first_chunk = (t_chunk *)(*chunks)->next->content;
	last_chunk = (t_chunk *)(*chunks)->content;
	while (!is_in_chunk(best_node, first_chunk)
		&& !is_in_chunk(best_node, last_chunk))
	{
		rotate_chunks(chunks);
		first_chunk = (t_chunk *)(*chunks)->next->content;
		last_chunk = (t_chunk *)(*chunks)->content;
	}
	rotate_stacks(stacks, best_node);
}

void	push_node(t_stacks **stacks, t_list **chunks)
{
	t_chunk	*first_chunk;
	t_chunk	*last_chunk;
	t_node	*node;

	first_chunk = (t_chunk *)(*chunks)->next->content;
	last_chunk = (t_chunk *)(*chunks)->content;
	node = (t_node *)(*stacks)->a;
	(*stacks)->a = node->next;
	(*stacks)->size_a--;
	ft_putstr_fd("pb\n", 1);
	if (is_in_chunk(node, first_chunk))
	{
		first_chunk->size++;
		node_addfront(&(first_chunk->nodes), node);
	}
	else if (is_in_chunk(node, last_chunk))
	{
		last_chunk->size++;
		node_addback(&(last_chunk->nodes), node);
		chunks_r("b", stacks);
	}
	(*stacks)->size_b++;
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
	while ((*stacks)->size_a > 2)
	{
		get_scores(*stacks, chunks);
		make_moves(stacks, &chunks);
		push_node(stacks, &chunks);
	}
}