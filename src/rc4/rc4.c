#include "rc4.h"

/////////////////////////////////
//
//			INCLUDES
//
/////////////////////////////////

#include <string.h>

/////////////////////////////////
//
//			KEY SCHEDULE
//
/////////////////////////////////

uint8_t	*rc4_cipher(rc4_t *ctx, uint8_t *in, uint8_t *out, size_t size, size_t *sout)
{
	size_t i = 0, j = 0;
	uint8_t	tmp = 0, byte = 0;
	uint8_t	*save = NULL;

	if (!in || !out || !size) return (NULL);
	
	save = out;
	
	for (i = 0; i < size; i++) {
		i = (i + 1) % 0x100;
		j = (j + ctx->s[i]) % 0x100;

		tmp = ctx->s[j];
		ctx->s[j] = ctx->s[i];
		ctx->s[i] = tmp;

		byte = ctx->s[(ctx->s[i] + ctx->s[j]) % 0x100];
		*out++ = (byte ^ *in++);
	}
	if (sout)
		*sout = out - save;
	return (save);
}

int	key_schedule(rc4_t *ctx, const char *key, size_t length)
{
	int i = 0, j = 0;

	if (length >= KEY_SIZE)
		return (1);
	strncpy((char *)ctx->k, key, length);
	for (i = 0; i < 0x100; i++)
		ctx->s[i] = i;
	for (i = 0; i < 0x100; i++) {
		j = (j + ctx->s[i] + ctx->k[i % length]) % 0x100;
		ctx->s[i] ^= ctx->s[j];
		ctx->s[j] ^= ctx->s[i];
		ctx->s[i] ^= ctx->s[j];
	}
	return (0);
}
