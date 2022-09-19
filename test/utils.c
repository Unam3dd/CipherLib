#include <stdio.h>
#include <string.h>
#include "hex.h"
#include "base64.h"
#include "aes.h"
#include "utils.h"

int main(int ac, char **av)
{
	if (ac < 2)
		return (fprintf(stderr, "usage : %s <data>\n", av[0]), 1);

	unsigned char	buf[0x100];
	memset(buf, 0, sizeof(buf));
	unsigned char	decoded[0x100];
	memset(decoded, 0, sizeof(decoded));
	unsigned char	base64_buf[0x100];
	size_t			writed = 0;
	size_t			readed = 0;

	__asm__ ("pxor %xmm13, %xmm13");
	register __uint128_t xmm13 __asm__ ("xmm13");
	register __uint128_t xmm12 __asm__ ("xmm12");
	printf("%llx%llx\n", (unsigned long long)(xmm13 >> 0x3F), (unsigned long long)(xmm13 & 0xFFFFFFFFFFFFFFFF));
	printf("%llx%llx\n", (unsigned long long)(xmm12 >> 0x3F), (unsigned long long)(xmm12 & 0xFFFFFFFFFFFFFFFF));

	if (!hex_encode((uint8_t *)av[1], buf, strlen((const char *)av[1]), sizeof(buf)))
		return (1);
	printf("Data str : %s | hex (%s)\n", av[1], buf);
	size_t len = strlen((const char *)buf);
	while (len) {
		buf[len] = (buf[len] >= 'A' && buf[len] <= 'F') ? buf[len] ^ 0x20 : buf[len];
		// for fun
		len = ~-len;
	}
	printf("Data lower : %s\n", buf);
	to_upper(buf);
	printf("Data Upper : %s\n", buf);
	to_lower(buf);
	printf("REData Lower : %s\n", buf);
	if (hex_decode(buf, decoded, strlen((const char *)buf), sizeof(decoded)))
		printf("Decoded %s\n", decoded);
	base64_encode((uint8_t *)av[1], base64_buf, strlen((const char *)av[1]), &writed);
	printf("%s\n", base64_buf);
	memset(decoded, 0, sizeof(decoded));
	base64_decode(base64_buf, decoded, strlen((char *)base64_buf), &writed);
	printf("%s\n%ld\n", decoded, writed);
	printf("CPU support AES : %d\n", check_cpu_support_aes() == AES_CPUID_VALUE);
	return (0);
}
