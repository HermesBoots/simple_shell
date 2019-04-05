#include <stddef.h>
#include "common.h"


SubString _strtok(char const *str, char const *delim)
{
	static char const *string;
	SubString ret = {NULL, 0};
	char const *delimiter;

	if (str != NULL)
		string = str;
	if (string == NULL)
		return (ret);
	for (; *string != '\0'; string++)
	{
		delimiter = delim;
		while (*delimiter != '\0' && *string != *delimiter)
			delimiter++;
		if (*delimiter == '\0')
		{
			ret.text = string;
			break;
		}
	}
	if (*string == '\0')
		return (ret);
	for (; *string != '\0'; string++)
	{
		delimiter = delim;
		while (*delimiter != '\0' && *string != *delimiter)
			delimiter++;
		if (*delimiter != '\0')
			break;
	}
	ret.length = string - ret.text;
	return (ret);
}
