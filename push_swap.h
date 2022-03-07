//
// Created by loichu on 07.03.22.
//

#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H
# include "libft/libft.h"
# include <stdlib.h>

typedef struct s_node
{
	int				val;
	int				score;
	struct s_node	*next;
}	t_node;

typedef struct s_stacks
{
	t_node	a;
	int		size_a;
	t_node 	b;
	int		size_b;
}	t_stacks;

typedef struct s_nodalyze
{
	int	val;
	int	ini;
}	t_nodalyze;

t_list	*analyze(char **input, int size);

void raise_error(int errcode);

#endif //PUSH_SWAP_H
