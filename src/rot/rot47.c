#include "rot.h"
#include <stddef.h>

char	*rot47_cipher(char *in, char *out, size_t length)
{
	size_t	i = 0;

	if (!out)
		out = in;
	for (i = 0; i < length; i++) {
		if (in[i] >= 33 && in[i] <= 126)
			out[i] = 33 + ((in[i] + 14) % 94);
		else
			out[i] = in[i];
	}
	out[i] = 0;
	return (out);
}
