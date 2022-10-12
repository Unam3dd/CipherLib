#include "rot.h"

/////////////////////////////////
//
//			Caesar Cipher
//
/////////////////////////////////

char	*caesar_cipher(char *in, char *out, char key)
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
		if (*in >> 4 != 4)
			*tmp++ = str[ ((*in++ - 'a') + key) % 26];
		else
			*tmp++ = str[ ((*in++ - 'A') + key) % 26] ^ 0x20;
	}
	*tmp = 0;
	return (out);
}
