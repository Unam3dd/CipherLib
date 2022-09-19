#include "xor.h"
#include "prng.h"
#include <stdio.h>
#include <string.h>
#include <emmintrin.h>

void print_m128i_with_string(char* string, __m128i data)
{
 	unsigned char *pointer = (unsigned char*)&data;
 	int i;
 	printf("%-40s[0x",string);
	for (i=0; i<16; i++)
		printf("%02x",pointer[i]);
	printf("]\n");
}

int main(int ac, char **av)
{
	__m128i	bytes[32];
	__m128i key[32];
	int		i;
	size_t	len = sizeof(bytes) / sizeof(__m128i);
	size_t	keylen = sizeof(key) / sizeof(__m128i);

	// Generate 32 range of 16 bytes

	for (i = 0; i < len; i++) {
		urandom((uint8_t *)&bytes[i], sizeof(__m128i));
		urandom((uint8_t *)&key[i], sizeof(__m128i));
	}

	// Show it in Hexa
	for (i = 0; i < len; i++)
		print_m128i_with_string("PLAINTEXT", bytes[i]);

	xor_cipher_128(bytes, len, key, keylen);

	for (i = 0; i < len; i++)
		print_m128i_with_string("XORED", bytes[i]);

	xor_cipher_128(bytes, len, key, keylen);

	for (i = 0; i < len; i++)
		print_m128i_with_string("UNXORED", bytes[i]);

	return (0);
}
