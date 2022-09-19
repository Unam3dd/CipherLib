#include "utils.h"

//////////////////////////////////
//
//			TO UPPER
//
//////////////////////////////////

char	*to_upper(char *data)
{
	char	*tmp = NULL;

	if (!data)
		return (NULL);
	tmp = data;
	while (*tmp) {
		*tmp = ((*tmp >= 'a' && *tmp <= 'z') ? (*tmp ^ 0x20) : *tmp);
		tmp++;
	}
	*tmp = 0;
	return (data);
}
