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


SubString _strtok(char const *str, char const *delim);

#endif
