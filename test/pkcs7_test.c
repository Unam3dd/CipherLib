#include "pkcs7.h"
#include "prng.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

void	show_data(unsigned char *buf, size_t len)
{
	for (int i = 0; i < len; i++)
		printf("%02x", buf[i]);
}

int main(void)
{
	unsigned char	msg[0x20];

	memset(msg, 0, sizeof(msg));
	urandom(msg, 18);
	show_data(msg, sizeof(msg));
	get_padding_size(msg, 18, sizeof(msg));
	printf("\n");
	show_data(msg, sizeof(msg));
	return (0);
}
