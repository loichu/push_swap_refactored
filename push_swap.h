//
// Created by loichu on 07.03.22.
//

#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H
# include "libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>

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

typedef struct	s_chunk
{
	int 	max_size;
	int 	size;
	int 	min;
	int 	max;
	t_node	*nodes;
	//int cursor;
}	t_chunk;

t_node	*analyze(char **input, int size);

void	node_addback(t_node **list, t_node *new);
void	node_addfront(t_node **list, t_node *new);

t_node *new_node(int val);

void	presort(t_stacks **stacks);

int 	abs(int x);
int 	max(int x, int y);
int 	min(int x, int y);

//void	_rotate_chunks(t_list **chunks);
//void	_reverse_rotate_chunks(t_list **chunks);
void	rotate_chunks(t_list **chunks);
void	reverse_rotate_chunks(t_list **chunks);


void 	raise_error(int errcode);

void	r(char *cmd, t_stacks **stacks);
void	chunks_r(char *cmd, t_stacks **stacks);
void	p(char stack, t_stacks **stacks);
void	p_chunk(t_list **chunks, t_stacks **stacks);

#endif //PUSH_SWAP_H
