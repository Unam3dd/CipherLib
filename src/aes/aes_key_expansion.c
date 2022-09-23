#include "aes.h"
#include "aes_inlines.h"
#include <stdio.h>

//////////////////////////////////
//
//		AES KEY EXPANSION 128
//
//		From Intel documentation
//		
//////////////////////////////////

void	AES_128_KEY_EXPANSION(const uint8_t *key, aes_key_t *buf)
{
	__m128i	tmp1, tmp2;
	tmp1 = _mm_loadu_si128((__m128i *)key); // Load key in 128 bits registers
	__m128i	*sched = (__m128i *)buf->key;

	sched[0] = tmp1;
	
	tmp2 = _mm_aeskeygenassist_si128(tmp1, 0x1);	// Generate key with Round Constant
	tmp1 = AES_128_ASSIST(tmp1, tmp2);
	sched[1] = tmp1;

	tmp2 = _mm_aeskeygenassist_si128(tmp1, 0x2);
	tmp1 = AES_128_ASSIST(tmp1, tmp2);
	sched[2] = tmp1;

	tmp2 = _mm_aeskeygenassist_si128(tmp1, 0x4);
	tmp1 = AES_128_ASSIST(tmp1, tmp2);
	sched[3] = tmp1;

	tmp2 = _mm_aeskeygenassist_si128(tmp1, 0x8);
	tmp1 = AES_128_ASSIST(tmp1, tmp2);
	sched[4] = tmp1;

	tmp2 = _mm_aeskeygenassist_si128(tmp1, 0x10);
	tmp1 = AES_128_ASSIST(tmp1, tmp2);
	sched[5] = tmp1;

	tmp2 = _mm_aeskeygenassist_si128(tmp1, 0x20);
	tmp1 = AES_128_ASSIST(tmp1, tmp2);
	sched[6] = tmp1;

	tmp2 = _mm_aeskeygenassist_si128(tmp1, 0x40);
	tmp1 = AES_128_ASSIST(tmp1, tmp2);
	sched[7] = tmp1;

	tmp2 = _mm_aeskeygenassist_si128(tmp1, 0x80);
	tmp1 = AES_128_ASSIST(tmp1, tmp2);
	sched[8] = tmp1;

	tmp2 = _mm_aeskeygenassist_si128(tmp1, 0x1b);
	tmp1 = AES_128_ASSIST(tmp1, tmp2);
	sched[9] = tmp1;

	tmp2 = _mm_aeskeygenassist_si128(tmp1, 0x36);
	tmp1 = AES_128_ASSIST(tmp1, tmp2);
	sched[10] = tmp1;
}
