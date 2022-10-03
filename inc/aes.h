#ifndef AES_H
#define AES_H

//////////////////////////////////
//
//			INCLUDES
//
//////////////////////////////////

#include "cpuid.h"
#include <stdint.h>
#include <stddef.h>
#include <wmmintrin.h>

//////////////////////////////////
//
//			DEFINES
//
//////////////////////////////////

#define AES_CPUID_VALUE 	0x2000000
#define AES_KEY_MAX_ROUND 	0x10
#define AES_TABLE_SIZE		0x6
#define AES_IV_SIZE			0x10

//////////////////////////////////
//
//			ROUND CONSTANT
//
//////////////////////////////////

#define RCON_CONSTANT(x) ((x<<1) ^ (0x11b & -(x>>7)))

//////////////////////////////////
//
//			SUPPORT AES-NI
//
//////////////////////////////////

int	check_cpu_support_aes(void);

//////////////////////////////////
//
//			TYPEDEFS
//
//////////////////////////////////

typedef struct 	aes_key_t		aes_key_t;
typedef enum   	aes_flag_t		aes_flag_t;
typedef enum	aes_rounds_t	aes_rounds_t;
typedef	int		(*aes_cb_t)(uint8_t *, uint8_t *, size_t, aes_key_t *);

//////////////////////////////////
//
//			ENUM
//
//////////////////////////////////

enum	aes_flag_t
{
	AES_ECB_128,
	AES_CBC_128
};

enum	aes_rounds_t
{
	AES_ROUNDS_128 = 0xA,
	AES_ROUNDS_192 = 0xC,
	AES_ROUNDS_256 = 0xE
};

//////////////////////////////////
//
//			STRUCTS
//
//////////////////////////////////

struct aes_key_t
{
	__m128i	key[AES_KEY_MAX_ROUND];
	uint8_t	iv[AES_IV_SIZE];
	int		nr;
};

//////////////////////////////////
//
//	  PRINT 128 XMM REGISTERS
//
//////////////////////////////////

void print_m128i_with_string(char* string,__m128i data);

//////////////////////////////////
//
//		KEY EXPANSION ALGORITHMS
//
//////////////////////////////////

void	AES_128_KEY_EXPANSION(const uint8_t *key, aes_key_t *buf);
void	AES_128_KEY_INV_EXPANSION(aes_key_t *keys, aes_key_t *buf);

//////////////////////////////////
//
//			AES 128 ECB
//
//////////////////////////////////

int	aes_ecb_encrypt(uint8_t *in, uint8_t *out, size_t length, aes_key_t *sched);
int	aes_ecb_decrypt(uint8_t *in, uint8_t *out, size_t length, aes_key_t *sched);

/////////////////////////////////
//
//			AES 128 CBC
//
/////////////////////////////////

int	aes_cbc_encrypt(uint8_t *in, uint8_t *out, size_t length, aes_key_t *sched);
int	aes_cbc_decrypt(uint8_t	*in, uint8_t *out, size_t length, aes_key_t *sched);

#endif
