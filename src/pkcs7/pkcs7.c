#include "pkcs7.h"

//////////////////////////////////
//
//			PKCS7
//
//////////////////////////////////


int	write_padding_size(uint8_t *buf, size_t length, size_t block_size)
{
	if (!buf)
		return (0);
	
	size_t pad = (block_size - ((length) % block_size));
	if (pad == block_size)
		return (0);
	for (int i = 0; i < (int)pad; i++)
		buf[length + i] = (char)pad;
	return (0);
}
