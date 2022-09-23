#include "aes.h"
#include <stdio.h>

//////////////////////////////////
//
//			AES UTILS
//
//////////////////////////////////

void print_m128i_with_string(char* string,__m128i data)
{
	unsigned char *pointer = (unsigned char*)&data;
	int i;
	
	printf("%-40s[0x",string);
	for (i=0; i<16; i++)
		printf("%02x",pointer[i]);
	printf("]\n");
}
