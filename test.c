
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
	int r = atoi(av[1]);
	int g = atoi(av[2]);
	int b = atoi(av[3]);
	int res = 0;

	res = b + g * 256 + r * 256 * 256;

	printf("res: %d\nhexa: %x\n", res, res);
	return 1;

}