#include "xor.h"


//////////////////////////////////
//
//			XOR 32 Bits
//
//////////////////////////////////

uint32_t	*xor_cipher_u32(uint32_t *buf, size_t len, uint32_t *key, size_t keylen)
{
	if (!buf || !len || !key || !keylen)
		return (NULL);
	for (size_t i = 0; i < len; i++)
		buf[i] ^= key[i % keylen];
	return (buf);
}

uint32_t	*xor_cipher_output_u32(uint32_t *buf, uint32_t *out, size_t len, size_t outlen, uint32_t *key, size_t keylen)
{
	if (!buf || !len || !outlen || !key || !keylen)
		return (NULL);
	for (size_t i = 0; i < len; i++)
		out[i] = (buf[i] ^ key[i % keylen]);
	return (out);
}
uint32_t	*xor_cipher_one_out_u32(uint32_t *buf, uint32_t *out, size_t len, size_t outlen, uint32_t key)
{
	if (!buf || !out || !len || !outlen || (len > outlen))
		return (NULL);
	for (size_t i = 0; i < len; i++)
		out[i] = (buf[i] ^ key);
	return (out);
}

uint32_t	*xor_cipher_one_u32(uint32_t *buf, size_t len, uint32_t key)
{
	if (!buf || !len)
		return (NULL);
	for (size_t i = 0; i < len; i++)
		buf[i] ^= key;
	return (buf);
}
