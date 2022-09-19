#include "xor.h"

//////////////////////////////////
//
//			XOR CIPHER
//
//////////////////////////////////

// Xor bytes per bytes with len and key % keylen
uint8_t	*xor_cipher(uint8_t	*buf, size_t len, uint8_t *key, size_t keylen)
{
	if (!buf || !len || !key || !keylen)
		return (NULL);
	for (size_t i = 0; i < len; i++)
		buf[i] ^= key[i % keylen];
	return (buf);
}

// Xor bytes per bytes with len and key % keylen and store it in out buffer
uint8_t	*xor_cipher_out(uint8_t *buf, uint8_t *out, size_t len, size_t outlen, uint8_t *key, size_t keylen)
{
	if (!buf || !out || !len || !outlen || !key || !keylen)
		return (NULL);
	if ((len > outlen))
		return (NULL);
	for (size_t i = 0; i < len; i++)
		out[i] = (buf[i] ^ key[i % keylen]);
	return (out);
}

uint8_t	*xor_cipher_one_out(uint8_t *buf, uint8_t *out, size_t len, size_t outlen, uint8_t key)
{
	if (!buf || !len || (len > outlen))
		return (NULL);
	for (size_t i = 0; i < len; i++)
		out[i] = (buf[i] ^ key); 
	return (out);
}

// Xor cipher with one byte for each bytes

uint8_t	*xor_cipher_one(uint8_t *buf, size_t len, uint8_t key)
{
	if (!buf || !len)
		return (NULL);
	for (size_t i = 0; i < len; i++)
		buf[i] ^= key;
	return (buf);
}
