#include "base32.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

int main(int ac, char **av)
{
	if (ac < 2)
		return (1);
	uint8_t	buf[0x100];
	uint8_t	decode[0x100];
	size_t	len = 0, dlen = 0;

	memset(decode, 0, sizeof(decode));
	base32_encode((uint8_t *)av[1], buf, atoi(av[2]), &len);
	printf("%s | Len : %ld\n", buf, len);
	base32_decode(buf, decode, len, &dlen);
	printf("Decoded : %s\n", decode);
	return (0);
}
