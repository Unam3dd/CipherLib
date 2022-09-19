#include "xor.h"

//////////////////////////////////
//
//			XOR 128 Bits
//
//////////////////////////////////

__m128i	*xor_cipher_128(__m128i	*buf, size_t len, __m128i *key, size_t keylen)
{
	if (!buf || !len || !key)
		return (NULL);
	for (size_t i = 0; i < len; i++)
		buf[i] = _mm_xor_si128(buf[i], key[i % keylen]);
	return (buf);
}

__m128i	*xor_cipher_output_128(__m128i *buf, __m128i *out, size_t len, size_t outlen, __m128i *key, size_t keylen)
{
	if (!buf || !out || !len || !outlen || !key || !keylen)
		return (NULL);
	if (len > outlen)
		return (NULL);
	for (size_t i = 0; i < len; i++)
		out[i] = _mm_xor_si128(buf[i], key[i % keylen]);
	return (buf);
}

__m128i	*xor_cipher_one_out_128(__m128i *buf, __m128i *out, size_t len, size_t outlen, __m128i key)
{
	if (!buf || !out || !len || !outlen)
		return (NULL);
	if (len > outlen)
		return (NULL);
	for (size_t i = 0; i < len; i++)
		out[i] = _mm_xor_si128(buf[i], key);
	return (out);
}

__m128i	*xor_cipher_one_128(__m128i *buf, size_t len, __m128i key)
{
	if (!buf || !len)
		return (NULL);
	for (size_t i = 0; i < len; i++)
		buf[i] = _mm_xor_si128(buf[i], key);
	return (buf);
}
