#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rot.h"

int main(int ac, char **av)
{
	char	buf[0x100];

	if (ac < 3)
		return (1);
	memset(buf, 0, sizeof(buf));
	caesar_cipher(av[1], buf, atoi(av[2]));
	printf("%s\n", buf);
	return (0);
}
