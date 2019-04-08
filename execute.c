#include <unistd.h>
#include <errno.h>
#include <unistd.h>
#include "common.h"


#define MIN(a, b) (a < b ? a : b)


/**
 * find_command - searches for path to argv[0]
 * @argv: argv array to be given to child process
 *
 * Description: This function doesn't modify argv, but it does store the
 * resulting path in globals.command and sets globals.command_len appropriately
 *
 * Return: 1 if command exists, 0 if it doesn't
 */
char find_command(char **argv)
{
	size_t index;
	SubString tok;

	globals.command_len = 0;
	for (index = 0; index < 4095; index++)
	{
		if (argv[0][index] == '/')
		{
			errno = 0;
			if (access(argv[0], F_OK) == 0)
			{
				index = _strncpy(globals.command, argv[0], 4096);
				globals.command_len = index;
				return (1);
			}
			else
			{
				error();
				globals.command[0] = '\0';
				return (0);
			}
		}
	}
	tok = _strtok(globals.path, ":");
	while (tok.text != NULL)
	{
		index = _strncpy(globals.command, tok.text, MIN(tok.length, 4096));
		index += _strncpy(globals.command, argv[0], 4096 - index);
		errno = 0;
		if (access(globals.command, F_OK) == 0)
		{
			globals.command_len = index;
			return (1);
		}
		tok = _strtok(NULL, ":");
	}
	errno = ENOENT;
	error();
	globals.command[0] = '\0';
	return (0);
}
