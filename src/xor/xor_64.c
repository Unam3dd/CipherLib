#include "xor.h"

//////////////////////////////////
//
//			XOR 64 Bits
//
//////////////////////////////////

uint64_t	*xor_cipher_u64(uint64_t *buf, size_t len, uint64_t *key, size_t keylen)
{
	if (!buf || !len || !key || !keylen)
		return (NULL);
	for (size_t i = 0; i < len; i++)
		buf[i] ^= key[i % keylen];
	return (buf);
}

uint64_t	*xor_cipher_output_u64(uint64_t *buf, uint64_t *out, size_t len, size_t outlen, uint64_t *key, size_t keylen)
{
	if (!buf || !out || !len || !outlen || !key || !keylen)
		return (NULL);
	if (len > outlen)
		return (NULL);
	for (size_t i = 0; i < len; i++)
		out[i] = (buf[i] ^ key[i % keylen]);
	return (out);
}

uint64_t	*xor_cipher_one_out_u64(uint64_t *buf, uint64_t *out, size_t len, size_t outlen, uint64_t key)
{
	if (!buf || !out || !len || !outlen || (len > outlen))
		return (NULL);
	for (size_t i = 0; i < len; i++)
		out[i] = (buf[i] ^ key);
	return (out);
}

uint64_t	*xor_cipher_one_u64(uint64_t *buf, size_t len, uint64_t key)
{
	if (!buf || !len)
		return (NULL);
	for (size_t i = 0; i < len; i++)
		buf[i] ^= key;
	return (buf);
}
