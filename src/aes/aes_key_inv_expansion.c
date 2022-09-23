#include "aes.h"

//////////////////////////////////
//
//		AES KEY INV EXPANSION
//
//////////////////////////////////

void	AES_128_KEY_INV_EXPANSION(aes_key_t *keys, aes_key_t *buf)
{
	int	i;

	if (!keys || !buf) return ;

	_mm_storeu_si128(&buf->key[AES_ROUNDS_128], keys->key[0]);
	for (i = 1; i < AES_ROUNDS_128; i++)
		buf->key[AES_ROUNDS_128 - i] = _mm_aesimc_si128(keys->key[i]);
	_mm_storeu_si128(&buf->key[0], keys->key[AES_ROUNDS_128]);
}
