#include "xor.h"
#include "prng.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

int main(int ac, char **av)
{
	uint8_t	bytes[0x100];
	uint8_t	key[32];
	int		i;

	if (ac < 2)
		return (fprintf(stderr, "usage : %s <data>\n", av[0]), 1);

	strncpy((char *)bytes, av[1], 0x100);
	urandom(key, 32);
	printf("Message : %s\nBuffer : ", (char *)bytes);
	for (i = 0; bytes[i]; i++)
		printf("%x", bytes[i]);
	printf("\n");
	xor_cipher(bytes, strlen((char *)bytes), key, sizeof(key));
	for (i = 0; bytes[i]; i++)
		printf("%x", bytes[i]);
	printf("\n");
	xor_cipher(bytes, strlen((char *)bytes), key, sizeof(key));
	for (i = 0; bytes[i]; i++)
		printf("%x", bytes[i]);
	printf("\n");
	printf("Message Unxored : %s\n", (char *)bytes);
	return (0);
}
