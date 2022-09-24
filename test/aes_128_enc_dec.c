#include "aes.h"
#include "prng.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

void	show_data(unsigned char *data, size_t len)
{
	for (int i = 0; i < len; i++)
		printf("%02x", data[i]);
}

void	show_keys(aes_key_t *keys)
{
	for (int i = 0; i < AES_ROUNDS_128; i++)
		print_m128i_with_string("KEY", keys->key[i]);
}

int main(void)
{
	aes_key_t		sched[2];
	unsigned char	buf[0x100];
	unsigned char	dec[0x40];
	unsigned char	key[0x10];
	unsigned char	msg[0x40];

	sched[0].nr = AES_ROUNDS_128;
	sched[1].nr = AES_ROUNDS_128;

	memset(buf, 0, sizeof(buf));
	memset(key, 0, sizeof(key));
	memset(msg, 0, sizeof(msg));
	urandom(msg, sizeof(msg));
	urandom(key, sizeof(key));
	printf("Our key : \n");
	show_data(key, sizeof(key));
	printf("\n");

	printf("Our Data Message :\n");
	show_data(msg, sizeof(msg));
	printf("\n");

	AES_128_KEY_EXPANSION(key, &sched[0]);
	AES_128_KEY_INV_EXPANSION(&sched[0], &sched[1]);

	printf("Key expansion keys schedule\n");
	show_keys(&sched[0]);
	printf("Invert Key expansion key schedule\n");
	show_keys(&sched[1]);

	aes_128_ecb_encrypt(msg, buf, sizeof(msg), &sched[0]);

	printf("Output :\n");
	show_data(buf, sizeof(buf));
	printf("\n");

	aes_128_ecb_decrypt(buf, dec, sizeof(buf), &sched[1]);

	printf("Unciphered data :\n");
	show_data(dec, sizeof(dec));

	return (0);
}
