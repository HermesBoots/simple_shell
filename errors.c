#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "common.h"



/**
 * error - print an error message and possibly exit
 * @message: custom error message if desired
 */
void error(char *message)
{
	size_t index;

	if (errno == 0)
		return;
	index = _strncpy(globals.outbuf, globals.self.text, globals.self.length);
	index += _strncpy(globals.outbuf + index, ": ", 2);
	index += print_int(globals.outbuf + index, globals.line_num);
	index += _strncpy(globals.outbuf + index, ": ", 2);
	write(STDERR_FILENO, globals.outbuf, index);
	if (message != NULL)
	{
		write(STDERR_FILENO, globals.command.text, globals.command.length);
		write(STDERR_FILENO, ": ", 2);
		for (index = 0; message[index] != '\0'; index++)
			;
		write(STDERR_FILENO, message, index);
	}
	else
	{
		perror(globals.command.text);
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
		exit(globals.last_status);
}
