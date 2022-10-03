#ifndef PKCS7_H
#define PKCS7_H

//////////////////////////////////
//
//			PKCS7
//
//////////////////////////////////


//////////////////////////////////
//
//			INCLUDES
//
//////////////////////////////////

#include <stdint.h>
#include <stddef.h>

//////////////////////////////////
//
//			REFERENCE
//
//////////////////////////////////

/*
 * 
 * Wikipedia : https://en.wikipedia.org/wiki/Padding_(cryptography)#PKCS#5_and_PKCS#7
 *
 * 	This padding method (as well as the previous two) is well-defined if and only if N is less than 256.
 *
 * Example: In the following example the block size is 8 bytes and padding is required for 4 bytes
 *
 * ... | DD DD DD DD DD DD DD DD | DD DD DD DD 04 04 04 04 |
 *
*/

int	write_padding_size(uint8_t *buf, size_t len, size_t block_size);

#endif
