#include "utils.h"

//////////////////////////////////
//
//			TO LOWER
//
//////////////////////////////////

char	*to_lower(char *data)
{
	char	*tmp = NULL;

	if (!data)
		return (NULL);
	tmp = data;
	while (*tmp) {
		*tmp = (*tmp >= 'A' && *tmp <= 'Z') ? (*tmp ^ 0x20) : *tmp;
		tmp++;
	}
	*tmp = 0;
	return (data);
}
