#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "common.h"



/**
 * error - print an error message and possibly exit
 * @command: first word on line being executed
 */
void error(char *command)
{
	size_t index = 0;

	if (errno == 0)
		return;
	index = globals.self_len;
	index += _strncpy(globals.self + index, ": ", 2);
	index += print_int(globals.self + index, globals.line_num);
	index += _strncpy(globals.self + index, ": ", 2);
	write(STDERR_FILENO, globals.self, index);
	globals.self[globals.self_len] = '\0';
	if (errno != ENOENT && errno != ENOTDIR)
	{
		perror(globals.command);
	}
	else
	{
		if (command != NULL)
		{
			index = _strncpy(globals.command, command, 4096);
			index += _strncpy(globals.command + index, ": ", 2);
		}
		index += _strncpy(globals.command + index, "not found\n", 10);
		write(STDERR_FILENO, globals.command, index);
	}
	if (errno == EACCES)
		globals.last_status = 126;
	else if (errno == ENOENT)
		globals.last_status = 127;
	else
		globals.last_status = 2;
	if (
		errno != ENOENT && errno != ENOTDIR && errno != EACCES &&
		errno != ENAMETOOLONG && errno != ENOEXEC && errno != EPERM &&
		errno != ELOOP && errno != ETXTBSY
	)
	{
		free(globals.line);
		free(command);
		exit(globals.last_status);
	}
}
