#include "aes.h"

//////////////////////////////////
//
//		AES 128 ECB
//
//////////////////////////////////

int	aes_ecb_encrypt(uint8_t *in, uint8_t *out, size_t length, aes_key_t *sched)
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
		for (j = 1; j < sched->nr; j++)
			tmp = _mm_aesenc_si128(tmp, sched->key[j]);
		tmp = _mm_aesenclast_si128(tmp, sched->key[j]);
		_mm_storeu_si128(&((__m128i *)out)[i], tmp);
	}
	return (0);
}

int	aes_ecb_decrypt(uint8_t *in, uint8_t *out, size_t length, aes_key_t *sched)
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
		for (j = 1; j < sched->nr; j++)
			tmp = _mm_aesdec_si128(tmp, sched->key[j]);
		tmp = _mm_aesdeclast_si128(tmp, sched->key[j]);
		_mm_storeu_si128(&((__m128i *)out)[i], tmp);
	}
	return (0);
}

/////////////////////////////////
//
//			AES 128 CBC
//
/////////////////////////////////

int	aes_cbc_encrypt(uint8_t *in, uint8_t *out, size_t length, aes_key_t *sched)
{
	if (!in || !out || !length || !sched) return (1);
	
	__m128i data, fback;
	int	i, j;

	if (length & 0xF)
		length = (length >> 4) + 1;
	else
		length >>= 4;
	fback = _mm_loadu_si128((__m128i*)sched->iv);
	for (i = 0; i < (int)length; i++) {
		data = _mm_loadu_si128(&((__m128i*)in)[i]);
		fback = _mm_xor_si128(data, fback);
		fback = _mm_xor_si128(fback, ((__m128i*)sched->key)[0]);
		for (j = 1; j < (int)sched->nr; j++)
			fback = _mm_aesenc_si128(fback, ((__m128i*)sched->key)[j]);
		fback = _mm_aesenclast_si128(fback, ((__m128i*)sched->key)[j]);
		_mm_storeu_si128(&((__m128i*)out)[i], fback);
	}
	return (0);
}

int	aes_cbc_decrypt(uint8_t *in, uint8_t *out, size_t length, aes_key_t *sched)
{
	if (!in || !out || !length || !sched) return (1);

	__m128i data, fback, last;
	int i, j;
	
	if (length & 0xF)
		length = (length >> 4) + 1;
	else
		length >>= 4;
	fback = _mm_loadu_si128((__m128i*)sched->iv);
	for (i = 0; i < (int)length; i++) {
		last = _mm_loadu_si128(&((__m128i*)in)[i]);
		data = _mm_xor_si128(last, ((__m128i*)sched->key)[0]);
		for (j = 1; j < (int)sched->nr; j++)
			data = _mm_aesdec_si128(data, ((__m128i*)sched->key)[j]);
		data = _mm_aesdeclast_si128(data, ((__m128i*)sched->key)[j]);
		data = _mm_xor_si128(data, fback);
		_mm_storeu_si128(&((__m128i*)out)[i], data);
		fback = last;
	}
	return (0);
}
