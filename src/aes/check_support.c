#include "aes.h"

//////////////////////////////////
//
//			SUPPORT AES-NI
//
//////////////////////////////////

int	check_cpu_support_aes(void)
{
	unsigned int a,b,c,d;
	cpuid(1, a,b,c,d);
	return (c & AES_CPUID_VALUE);
}
