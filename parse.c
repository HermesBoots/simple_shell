#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "common.h"


/**
 * parse - parse a string
 * @str: string to parse
 *
 * Return: an array of strings
 */
char **parse(char *str)
{
	size_t total = 0;
	int count = 0;
	SubString token;
	char **ret;

	token = _strtok(str, " \n\t\r;");
	globals.command = token;
	while (token.text != NULL)
	{
		if (token.text[0] == '#')
			break;
		count++;
		total += token.length;
		token = _strtok(NULL, " \n\t\r;");
	}
	if (count == 0)
		return (NULL);
	ret = malloc(sizeof(char *) * (count + 1) + total + count);
	if (ret == NULL)
	{
		free(str);
		error(NULL);
	}
	ret[0] = (char *)(ret + count + 1);
	ret[count] = NULL;
	token = _strtok(str, " \n\t\r;");
	total = 0, count = 0;
	while (token.text != NULL)
	{
		if (token.text[0] == '#')
			break;
		ret[count] = ret[0] + total;
		total += token.length + 1;
		_memcpy(ret[count], token.text, token.length);
		ret[count][token.length] = '\0';
		count++;
		token = _strtok(NULL, " \n\t\r;");
	}
	return (ret);
}
