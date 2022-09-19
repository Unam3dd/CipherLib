#include "base64.h"
#include <string.h>

//////////////////////////////////
//
//			REF
//
//////////////////////////////////
//ref : https://fr.wikipedia.org/wiki/Base64

//////////////////////////////////
//
//			ENCODER
//
//////////////////////////////////

uint8_t	*base64_encode(uint8_t *data, uint8_t *out, size_t len, size_t *len_enc)
{
	uint32_t	block = 0;
	uint8_t		bytes[3] = {0, 0, 0};
	uint8_t		pad[3] = {0, 2, 1}; // (len % 3) == 1, its '==', (len % 3) == 2 is '='
	size_t		index = 0;

	for (size_t i = 0; i < len; i++) {

		bytes[0] = (i < len ? ((uint8_t)data[i++]) : 0);
		bytes[1] = (i < len ? ((uint8_t)data[i++]) : 0);
		bytes[2] = (i < len ? ((uint8_t)data[i]) : 0);

		block = (bytes[0] << 0x10) | (bytes[1] << 0x8) | (bytes[2]);

		out[index++] = (BASE64_TABLE[(block >> 18) & 0x3F]); // 0x3F (111111)
		out[index++] = (BASE64_TABLE[(block >> 12) & 0x3F]);
		out[index++] = (BASE64_TABLE[(block >> 6) & 0x3F]);
		out[index++] = (BASE64_TABLE[(block) & 0x3F]);
	}
	
	// il reste exactement 3 octets à coder (24 bits), alors on obtient directement 4 caractères sans traitement 		complémentaire ;
	// il reste seulement 2 octets (16 bits) à coder, alors on ajoute à droite 2 bits à zéros pour former 3 caractères de l'alphabet (3×6 = 16+2 = 18 bits) suivis d'un quatrième caractère « = » en complément ;
	// il reste un seul octet (8 bits) à coder, alors on ajoute à droite 4 bits à zéros pour former 2 caractères de l'alphabet (2×6 = 8+4 = 12 bits) suivis de deux caractères « = » en complément.

	index -= pad[len % 3];
	for (int i = 0; i < pad[len % 3]; i++)
		out[index++] = '=';
	*len_enc = index;
	out[index] = 0;

	return (out);
}

//////////////////////////////////
//
//			DECODER
//
//////////////////////////////////

uint8_t	*base64_decode(uint8_t *data, uint8_t *out, size_t len, size_t *len_dec)
{
	if (!data || !out || ((len + (len >> 0x3e)) & 0x3))
		return (NULL);
	int	pad = 0;
	uint32_t block = 0;
	uint8_t	*tmp = (uint8_t *)strchr((char *)data, '=');
	if (tmp) {
		pad = strspn((char *)tmp, "=");
		memset(tmp, 0, pad);
		len -= pad;
	}
	tmp = out;
	for (int i = 0; i < (int)len; i += 4) {
		block = (BASE64D_TABLE[data[i]]) << 0x12 	 | (BASE64D_TABLE[data[i + 1]]) << 0xC;
		block |= (BASE64D_TABLE[data[i + 2]]) << 0x6 | (BASE64D_TABLE[data[i + 3]]);
		*tmp++ = (block >> 0x10) & 0xFF;
		*tmp++ = (block >> 0x8) & 0xFF;
		*tmp++ = (block) & 0xFF;
	}
	*len_dec = tmp - out;
	*tmp = 0;
	return (out);
}
