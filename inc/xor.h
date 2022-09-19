#ifndef XOR_H
#define XOR_H

//////////////////////////////////
//
//			INCLUDES
//
//////////////////////////////////

#include <stdint.h>
#include <stddef.h>
#include <emmintrin.h>

//////////////////////////////////
//
//			XOR ALGORITHM
//
//////////////////////////////////


//////////////////////////////////
//
//			XOR 8 Bits
//
//////////////////////////////////

uint8_t	*xor_cipher(uint8_t	*buf, size_t len, uint8_t *key, size_t keylen);
uint8_t	*xor_cipher_output(uint8_t *buf, uint8_t *out, size_t len, size_t outlen, uint8_t *key, size_t keylen);
uint8_t	*xor_cipher_one_out(uint8_t *buf, uint8_t *out, size_t len, size_t outlen, uint8_t key);
uint8_t	*xor_cipher_one(uint8_t *buf, size_t len, uint8_t key);

//////////////////////////////////
//
//			XOR 32 Bits
//
//////////////////////////////////

uint32_t	*xor_cipher_u32(uint32_t	*buf, size_t len, uint32_t *key, size_t keylen);
uint32_t	*xor_cipher_output_u32(uint32_t *buf, uint32_t *out, size_t len, size_t outlen, uint32_t *key, size_t keylen);
uint32_t	*xor_cipher_one_out_u32(uint32_t *buf, uint32_t *out, size_t len, size_t outlen, uint32_t key);
uint32_t	*xor_cipher_one_u32(uint32_t *buf, size_t len, uint32_t key);

//////////////////////////////////
//
//			XOR 64 Bits
//
//////////////////////////////////

uint64_t	*xor_cipher_u64(uint64_t	*buf, size_t len, uint64_t *key, size_t keylen);
uint64_t	*xor_cipher_output_u64(uint64_t *buf, uint64_t *out, size_t len, size_t outlen, uint64_t *key, size_t keylen);
uint64_t	*xor_cipher_one_out_u64(uint64_t *buf, uint64_t *out, size_t len, size_t outlen, uint64_t key);
uint64_t	*xor_cipher_one_u64(uint64_t *buf, size_t len, uint64_t key);

//////////////////////////////////
//
//			XOR 128 Bits
//
//////////////////////////////////

__m128i	*xor_cipher_128(__m128i	*buf, size_t len, __m128i *key, size_t keylen);
__m128i	*xor_cipher_output_128(__m128i *buf, __m128i *out, size_t len, size_t outlen, __m128i *key, size_t keylen);
__m128i	*xor_cipher_one_out_128(__m128i *buf, __m128i *out, size_t len, size_t outlen, __m128i key);
__m128i	*xor_cipher_one_128(__m128i *buf, size_t len, __m128i key);

#endif
