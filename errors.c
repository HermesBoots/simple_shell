#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "common.h"



/**
 * error - print an error message and possibly exit
 * @code: the error code as defined in errors.h
 */
void error()
{
	size_t index;

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
		index = globals.command_len;
		index += _strncpy(globals.command + index, ": not found\n", 12);
		write(STDERR_FILENO, globals.command, index);
		globals.command[globals.command_len] = '\0';
	}
	if (
		errno != ENOENT &&
		errno != ENOTDIR &&
		errno != EACCES &&
		errno != ENAMETOOLONG &&
		errno != ENOEXEC &&
		errno != EPERM &&
		errno != ELOOP &&
		errno != ETXTBSY
	)
		exit(errno);
}
