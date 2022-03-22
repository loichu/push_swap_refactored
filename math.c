//
// Created by loichu on 22.03.22.
//

int	abs(int x)
{
	if (x < 0)
		return (x * -1);
	return (x);
}

int	max(int x, int y)
{
	if (x > y)
		return (x);
	return (y);
}

int	min(int x, int y)
{
	if (x < y)
		return (x);
	return (y);
}