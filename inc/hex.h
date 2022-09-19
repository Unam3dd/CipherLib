#ifndef HEX_H
#define HEX_H

//////////////////////////////////
//
//			INCLUDES
//
//////////////////////////////////

#include <stdint.h>
#include <stddef.h>

//////////////////////////////////
//
//			HEX ENCODE
//
//////////////////////////////////

uint8_t	*hex_encode(uint8_t	*data, uint8_t *out, size_t d_len, size_t o_len);
uint8_t	*hex_decode(uint8_t *data, uint8_t *out, size_t d_len, size_t o_len);

#endif
