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

	token = _strtok(str, " \n\t\r");
	/* Finding dimensions of argv */
	while (token.text != NULL)
	{
		count++;
		total += token.length;
		token = _strtok(NULL, " \n\t\r");
	}
	if (count == 0)
		return (NULL);
	/* ret array allocation */
	ret = malloc(sizeof(char *) * (count + 1) + total + count);
	if (ret == NULL)
	{
		error(ERROR_MEMORY);
		return (NULL);
	}
	ret[0] = (char *)(ret + count + 1);
	ret[count] = NULL;
	token = _strtok(str, " \n\t\r");
	/* reseting to reuse variables */
	total = 0, count = 0;
	/* populating the ret array and filling in the strs they point to */
	while (token.text != NULL)
	{
		ret[count] = ret[0] + total;
		total += token.length + 1;
		_memcpy(ret[count], token.text, token.length);
		ret[count][token.length] = '\0';
		count++;
		token = _strtok(NULL, " \n\t\r");
	}
	return (ret);
}
