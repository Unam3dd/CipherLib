#ifndef AES_INLINES_H
#define AES_INLINES_H

//////////////////////////////////
//
//		128 Bits builtins
//
//////////////////////////////////

#include <emmintrin.h>

//////////////////////////////////
//
//			AES INLINES
//
//////////////////////////////////

inline	__m128i AES_128_ASSIST(__m128i t1, __m128i t2)
{
	__m128i t3;
	t2 = _mm_shuffle_epi32 (t2 ,0xff);
	t3 = _mm_slli_si128 (t1, 0x4);
	t1 = _mm_xor_si128 (t1, t3);
	t3 = _mm_slli_si128 (t3, 0x4);
	t1 = _mm_xor_si128 (t1, t3);
	t3 = _mm_slli_si128 (t3, 0x4);
	t1 = _mm_xor_si128 (t1, t3);
	t1 = _mm_xor_si128 (t1, t2);
	return (t1);
}

#endif
