#include "aes.h"

//////////////////////////////////
//
//		AES 128 ENC/DEC
//
//////////////////////////////////

int	aes_128_ecb_encrypt(uint8_t *in, uint8_t *out, size_t length, aes_key_t *sched)
{
	if (!in || !out || !length || !sched) return (1);
	__m128i	tmp;
	int	i, j;

	if (length & 0xF)
		length = (length >> 4) + 1;
	else
		length >>=4;
	for (i = 0; i < (int)length; i++) {
		tmp = _mm_loadu_si128(&((__m128i *)in)[i]);
		tmp = _mm_xor_si128(tmp, sched->key[0]);
		for (j = 1; j < AES_ROUNDS_128; j++)
			tmp = _mm_aesenc_si128(tmp, sched->key[j]);
		tmp = _mm_aesenclast_si128(tmp, sched->key[j]);
		_mm_storeu_si128(&((__m128i *)out)[i], tmp);
	}
	return (0);
}

int	aes_128_ecb_decrypt(uint8_t *in, uint8_t *out, size_t length, aes_key_t *sched)
{
	if (!in || !out || !length || !sched) return (1);
	__m128i tmp;
	int i, j;

	if (length & 0xF)
		length = (length >> 4) + 1;
	else
		length >>= 4;
	for (i = 0; i < (int)length; i++) {
		tmp = _mm_loadu_si128(&((__m128i *)in)[i]);
		tmp = _mm_xor_si128(tmp, sched->key[0]);
		for (j = 1; j < AES_ROUNDS_128; j++)
			tmp = _mm_aesdec_si128(tmp, sched->key[j]);
		tmp = _mm_aesdeclast_si128(tmp, sched->key[j]);
		_mm_storeu_si128(&((__m128i *)out)[i], tmp);
	}
	return (0);
}
