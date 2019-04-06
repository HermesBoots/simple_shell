#ifndef _COMMON_H_
#define _COMMON_H_

/**
 * struct SubString - enabling passing strings along with their lengths
 * @text: pointer to first byte in substring
 * @length: length of substring
 */
typedef struct SubString
{
	char const *text;
	size_t length;
} SubString;


void _memcpy(char *dest, char const *src, size_t count);
SubString _strtok(char const *str, char const *delim);

#endif
