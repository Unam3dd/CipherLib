#include "aes.h"
#include "prng.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

void	show_keys(aes_key_t *keys)
{
	for (int i = 0; i < AES_ROUNDS_128; i++)
		print_m128i_with_string("KEY", keys->key[i]);
}

int main(void)
{
	aes_key_t	sched[2];
	uint8_t		key[16];

	sched[0].nr = AES_ROUNDS_128;
	sched[1].nr = AES_ROUNDS_128;
	
	memset(sched[0].key, 0, sizeof(sched[0].key));
	memset(sched[1].key, 0, sizeof(sched[1].key));

	urandom(key, sizeof(key)); // Generate random key
	printf("Before key expansion algorithm !\n");
	show_keys(&sched[0]);
	AES_128_KEY_EXPANSION(key, &sched[0]);
	printf("After Key expansion algorithm !\n");
	show_keys(&sched[0]);

	printf("Before Key invert expansion algorithm !\n");
	show_keys(&sched[1]);
	printf("After Key Invert expansion algorithm !\n");
	AES_128_KEY_INV_EXPANSION(&sched[0], &sched[1]);
	show_keys(&sched[1]);

	return (0);
}
