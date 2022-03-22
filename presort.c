#include "push_swap.h"

t_list *init_chunks(int chunk_size, int nb_chunks, int last_chunk_size)
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

int	move_to_top(int index, int stack_size)
{
	if (index > stack_size / 2)
		index = (stack_size - index) * -1;
	return (index);
}

bool	is_in_chunk(t_node *node, t_chunk *chunk)
{
	//printf("check if %i is between %i and %i\n", node->val, chunk->min, chunk->max);
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

bool	print_chunk_node(t_chunk *chunk)
{
	static t_node	*node;
	static t_chunk 	*prev_chunk;

	if (!chunk)
		return (false);
	if (!node)
		node = chunk->nodes;
	if (node)
		printf("%i\t", node->val);
	else
		printf("\t");
	if (chunk != prev_chunk)
	{
		printf("Chunk: %i → %i\t", chunk->min, chunk->max);
		prev_chunk = chunk;
	}
	if (!node || !node->next)
	{
		printf("count: %i", chunk->size);
		node = NULL;
		return (false);
	}
	node = node->next;
	return (true);
}

void	print_stack_chunks(t_list *chunks, t_node *stack_a)
{
	t_chunk	*chunk;

	chunk = (t_chunk *)chunks->content;
	printf("A\tMA\tS\tMB\tB\n");
	printf("====================================\n");
	printf("\t\t\t\t");
	while (print_chunk_node(chunk))
	{
		printf("\n");
		printf("\t\t\t\t");
	}
	printf("\n");
	chunks = chunks->next;
	chunk = (t_chunk *)chunks->content;
	printf("%i\t%i\t%i\t%i\n", stack_a->val, stack_a->move_a, stack_a->score, stack_a->move_b);
	stack_a = stack_a->next;
	while (stack_a)
	{
		printf("%i\t%i\t%i\t%i\t", stack_a->val, stack_a->move_a, stack_a->score, stack_a->move_b);
		if (!print_chunk_node(chunk))
		{
			if (chunks->next)
			{
				chunks = chunks->next;
				chunk = (t_chunk *)chunks->content;
			}
			else
				chunk = NULL;
		}
		stack_a = stack_a->next;
		printf("\n");
	}
	while (chunks)
	{
		printf("\t\t\t\t");
		if (!print_chunk_node(chunk))
		{
			if (chunks->next)
			{
				chunks = chunks->next;
				chunk = (t_chunk *)chunks->content;
			}
			else
				chunks = NULL;
		}
		printf("\n");
	}
}

t_node	*get_best_node(t_node *stack)
{
	t_node	*best_node;

	best_node = NULL;
	while (stack)
	{
		if (stack->score >= 0
			&& (!best_node || stack->score < best_node->score))
			best_node = stack;
		stack = stack->next;
	}
	return (best_node);
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
		//printf("rotate chunks\n");
		rotate_chunks(chunks);
		first_chunk = (t_chunk *)(*chunks)->next->content;
		last_chunk = (t_chunk *)(*chunks)->content;
	}
	printf("------- rotate stacks -------\n");
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
	ft_putstr_fd("pb\n", 1);
}

void	presort(t_stacks **stacks)
{
	t_list	*chunks;
	int 	nb_chunks;
	int 	chunk_size;
	int 	last_chunk_size;
	char 	*press_enter;

	nb_chunks = 4;
	chunk_size = (*stacks)->size_a / nb_chunks;
	last_chunk_size = (*stacks)->size_a % chunk_size;
	if (last_chunk_size) {
		nb_chunks++;
	}
	chunks = init_chunks(chunk_size, nb_chunks, last_chunk_size);
	press_enter = "";
	while ((*stacks)->size_a > 2)
	{
		get_scores(*stacks, chunks);
		print_stack_chunks(chunks, (t_node *)(*stacks)->a);
		read(1, press_enter, 1);
		//printf("======= MAKE MOVES =======\n");
		make_moves(stacks, &chunks);
		//print_stack_chunks(chunks, (t_node *)(*stacks)->a);
		//printf("======= PUSH NODE =======\n");
		push_node(stacks, &chunks);
		//print_stack_chunks(chunks, (t_node *)(*stacks)->a);
	}
}