#include <stdio.h>
#include "push_swap.h"

t_stacks	*init_stacks(char **input, int size)
{
	t_stacks	*stacks;

	stacks = (t_stacks *)malloc(sizeof(t_stacks));
	if (!stacks)
		return (NULL);
	stacks->a = analyze(input, size);
	//printf("node: %p\n", stacks->a->next);
	stacks->size_a = size;
	printf("count: %i\n", stacks->size_a);
	stacks->b = NULL;
	stacks->size_b = 0;
	return (stacks);
}

int main(int argc, char **argv) {
	//t_node		*input;
	t_stacks	*stacks;

	// get input
	// analyze and validate input
	stacks = init_stacks(&(argv[1]), argc - 1);
	// transform input into stack
	// pre-sort in stack B
	//presort(&stacks);
	// sort in stack A

	return 0;
}
