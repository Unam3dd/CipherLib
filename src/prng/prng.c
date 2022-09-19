#include "prng.h"

//////////////////////////////////
//
//			INCLUDES
//
//////////////////////////////////

#include <stdio.h>
#include <immintrin.h> // _rdrand64_step

uint8_t	*urandom(uint8_t *buf, size_t length)
{
	if (!buf)
		return (NULL);
	FILE	*fp = fopen("/dev/urandom", "rb");
	if (!fp)
		return (NULL);
	if (fread(buf, sizeof(uint8_t), length, fp) != length)
		return (NULL);
	fclose(fp);
	return (buf);
}

uint8_t	*useed(uint8_t *buf, size_t length)
{
	unsigned int	data = 0;

	if (!buf || !length)
		return (NULL);
	for (size_t	i = 0; i < length; i++)
	{
		_rdrand32_step(&data);
		buf[i]   = (i < length) ? ((data >> 24) & 0xFF) : 0;
		buf[i+1] = (i+1 < length) ? ((data >> 16) & 0xFF) : 0;
		buf[i+2] = (i+2 < length) ? ((data >> 8)  & 0xFF) : 0;
		buf[i+3] = (i+3 < length) ? (data & 0xFF) : 0;
	}
	return (buf);
}
