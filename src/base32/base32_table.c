#include "base32.h"

/////////////////////////////////
//
//			BASE32 TABLE
//
/////////////////////////////////

const uint8_t	BASE32_TABLE[BASE32_TABLE_SIZE] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
	'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
	'Y', 'Z', '2', '3', '4', '5', '6', '7'
};

const uint8_t	BASE32_TABLE_DECODING[BASE32_TABLE_DECODING_SIZE] =  {
	0x2f, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 
	0, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 
	0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0x1, 0x2, 0x3, 0x4, 
	0x5, 0x6, 0x7, 0x8, 0x9, 0xa, 0xb, 
	0xc, 0xd, 0xe, 0xf, 0x10, 0x11, 0x12, 
	0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 
	0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0
};