#include "hex.h"

//////////////////////////////////
//
//			HEX DECODE
//
//////////////////////////////////

static char	get_nibble_byte(char c)
{
	return ((c >= 'a' && c <= 'f') ? (0xA + (c - 'a'))
			: (c >= 'A' && c <= 'F') ? (0xA + (c - 'A'))
			: (c & 0xF)
			);
}

uint8_t	*hex_decode(uint8_t *data, uint8_t *buf, size_t d_len, size_t o_len)
{
	uint8_t	*tmp = NULL;

	if (o_len <= d_len)
		return (NULL);
	if (!data || !buf)
		return (NULL);
	tmp = buf;
	while (d_len) {
		*tmp = get_nibble_byte(*data++);
		*tmp <<= 4;
		*tmp++ |= get_nibble_byte(*data++);
		d_len -= 2;
	}
	*tmp = 0;
	return (buf);
}
