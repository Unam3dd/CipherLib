#include "rot.h"

/////////////////////////////////
//
//			INCLUDES
//
/////////////////////////////////

#include <stddef.h>

/////////////////////////////////
//
//			ROT13
//
/////////////////////////////////

char	*rot13_cipher(char *in, char *out)
{
	char	str[] = "abcdefghijklmnopqrstuvwxyz";
	char	*tmp = NULL;

	if (!in)
		return (NULL);
	if (!out)
		out = in;
	tmp = out;
	while (*in)
	{
		if (!(*in >= 'a' && *in <= 'z') && !(*in >= 'A' && *in <= 'Z'))
			*tmp++ = *in++;
		if (*in >> 4 != 0x4)
			*tmp++ = str[(((*in++ - 'a') + 13)) % 0x1a];
		else
			*tmp++ = str[(((*in++ - 'A') + 13)) % 0x1a] ^ 0x20;
	}
	*tmp = 0;
	return (out);
}
