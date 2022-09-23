#include "prng.h"
#include <stdio.h>
#include <stdint.h>

int main(void)
{
	uint8_t	rnd[32];
	uint8_t	rndseed[16];

	urandom(rnd, sizeof(rnd));

	for (int i = 0; i < 32; i++)
		printf("%x", rnd[i]);
	printf("\n");
	useed(rndseed, sizeof(rndseed));
	for (int i = 0; i < 16; i++)
		printf("%02x", rndseed[i]);
	printf("\n");
	return (0);
}
