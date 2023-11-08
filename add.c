#include <stdio.h>
int main(int ac, char **av)
{
	return (printf("%d\n", av[1][0] * av[2][0]));
}