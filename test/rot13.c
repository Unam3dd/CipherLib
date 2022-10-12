#include <stdio.h>
#include <string.h>
#include "rot.h"

int main(int ac, char **av)
{
	char	buf[0x100];

	if (ac < 2)
		return (1);
	memset(buf, 0, sizeof(buf));
	rot13_cipher(av[1], buf);
	printf("%s\n", buf);
	return (0);
}
