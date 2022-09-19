#include "hex.h"
#include "hex_tab.h"

//////////////////////////////////
//
//			HEX ENCODE
//
//////////////////////////////////

uint8_t	*hex_encode(uint8_t *data, uint8_t *out, size_t d_len, size_t o_len)
{
	uint8_t	*tmp = NULL;

	if (o_len <= d_len)
		return (NULL);
	if (!data || !out)
		return (NULL);
	tmp = out;
	while (d_len) {
		*tmp++ = hex_tab[*data >> 4];
		*tmp++ = hex_tab[*data++ & 0xF];
		d_len--;
	}
	*tmp = 0;
	return (out);
}
