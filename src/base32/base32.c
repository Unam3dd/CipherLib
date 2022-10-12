#include "base32.h"
#include <stddef.h>
#include <string.h>

#include <stdio.h>

/////////////////////////////////
//
//			BASE32 ENCODER
//
/////////////////////////////////


uint8_t	*base32_encode(uint8_t *data, uint8_t *out, size_t length, size_t *len_enc)
{
	unsigned long long	tmp[5];
	unsigned long long 	bytes = 0;
	size_t				i = 0, j = 0;

	if (!data || !out)
		return (NULL);

	length = (((length << 3) % 5)) ? ((length << 3) / 5) + 1 : ((length << 3) / 5); 

	for (i = 0; i < length; i += 5, j += 8) {
		tmp[0] = (i < length ? data[i]   : 0);
		tmp[1] = (i+1 < length ? data[i+1] : 0);
		tmp[2] = (i+2 < length ? data[i+2] : 0);
		tmp[3] = (i+3 < length ? data[i+3] : 0);
		tmp[4] = (i+4 < length ? data[i+4] : 0);

		bytes = (tmp[0] << 0x20) | (tmp[1] << 0x18) | (tmp[2] << 0x10);
		bytes |= (tmp[3] << 0x8) | (tmp[4]);
		
		out[j] =   (j   < length ? (BASE32_TABLE[(bytes >> 35) & 0x1F]) 	: 0);
		out[j+1] = (j < length ? (BASE32_TABLE[(bytes >> 30) & 0x1F]) 		: 0);
		out[j+2] = (j < length ? (BASE32_TABLE[(bytes >> 25) & 0x1F]) 		: 0);
		out[j+3] = (j < length ? (BASE32_TABLE[(bytes >> 20) & 0x1F]) 		: 0);
		out[j+4] = (j < length ? (BASE32_TABLE[(bytes >> 15) & 0x1F]) 		: 0);
		out[j+5] = (j < length ? (BASE32_TABLE[(bytes >> 10) & 0x1F]) 		: 0);
		out[j+6] = (j < length ? (BASE32_TABLE[(bytes >> 5) & 0x1F]) 		: 0);
		out[j+7] = (j < length ? (BASE32_TABLE[(bytes & 0x1F)]) 		: 0);
	}

	j = length;
	
	for (i = 0; i < 8 - (length % 8) && (length % 8); i++)
		out[j++] = '=';
	out[j] = 0;
	
	if (len_enc)
		*len_enc = j;
	return (out);
}

/////////////////////////////////
//
//			BASE32 DECODER
//
/////////////////////////////////

uint8_t	*base32_decode(uint8_t *data, uint8_t *out, size_t length, size_t *len_dec)
{
	uint64_t	tmp[8];
	char		*pad = NULL;
	uint64_t	bytes = 0;
	size_t		i = 0, j = 0;
	
	if (!data || !length)
		return (NULL);
	pad = strchr((char *)data, '=');
	if (pad) {
		i = strspn(pad, "=");
		length -= i;
		memset(pad, 0, i);
	}
	for (i = 0; i < length; i += 8, j += 5) {
		tmp[0] = (i < length) ? BASE32_TABLE_DECODING[(data[i])] 	 : 0;
		tmp[1] = (i+1 < length) ? BASE32_TABLE_DECODING[(data[i+1])] : 0;
		tmp[2] = (i+2 < length) ? BASE32_TABLE_DECODING[(data[i+2])] : 0;
		tmp[3] = (i+3 < length) ? BASE32_TABLE_DECODING[(data[i+3])] : 0;
		tmp[4] = (i+4 < length) ? BASE32_TABLE_DECODING[(data[i+4])] : 0;
		tmp[5] = (i+5 < length) ? BASE32_TABLE_DECODING[(data[i+5])] : 0;
		tmp[6] = (i+6 < length) ? BASE32_TABLE_DECODING[(data[i+6])] : 0;
		tmp[7] = (i+7 < length) ? BASE32_TABLE_DECODING[(data[i+7])] : 0;

		bytes = (tmp[0] << 35) | (tmp[1] << 30) | (tmp[2] << 25);
		bytes |= (tmp[3] << 20) | (tmp[4] << 15) | (tmp[5] << 10);
		bytes |= (tmp[6] << 5) | (tmp[7]);

		out[j] 	 = (j < length) ? (bytes >> 0x20) & 0xFF   : 0;
		out[j+1] = (j+1 < length) ? (bytes >> 0x18) & 0xFF : 0;
		out[j+2] = (j+2 < length) ? (bytes >> 0x10) & 0xFF : 0;
		out[j+3] = (j+3 < length) ? (bytes >> 0x8) & 0xFF  : 0;
		out[j+4] = (j+4 < length) ? (bytes & 0xFF)		   : 0;
	}
	if (len_dec)
		*len_dec = length;
	out[j] = 0;
	return (out);
}

