#include "rot.h"
#include <stdio.h>
#include <string.h>

int main(int ac, char **av)
{
	if (ac < 2)
		return (fprintf(stderr, "usage : %s <data>\n", av[0]), 1);
	
	uint8_t	buf[0x100];
	size_t	len = 0; 

	memset(buf, 0, sizeof(buf));
	len = strlen(av[1]);
	rot47_cipher(av[1], buf, len);
	printf("ROT47: %s\n", buf);
	rot47_cipher(buf, NULL, len);
	printf("ROT47 REV : %s\n", buf);
	return (0);
}
