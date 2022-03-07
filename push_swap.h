//
// Created by loichu on 07.03.22.
//

#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H
# include "libft/libft.h"
# include <stdlib.h>
# include <stdio.h>

typedef struct s_node
{
	int				val;
	int				move_a;
	int				move_b;
	int				score;
	struct s_node	*next;
}	t_node;

typedef struct s_stacks
{
	t_node	*a;
	int		size_a;
	t_node 	*b;
	int		size_b;
}	t_stacks;

t_node	*analyze(char **input, int size);

t_node *new_node(int val);

void	presort(t_stacks **stacks);

void raise_error(int errcode);

#endif //PUSH_SWAP_H
