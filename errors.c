#include <stdlib.h>
#include <unistd.h>
#include "common.h"




/**
 * error - print an error message and possibly exit
 * @code: the error code as defined in errors.h
 */
void error(int code)
{
	static SubString errors[] = {
		{NULL, 0},
		{"not found", 10},
		{"Syntax error", 13},
		{"out of memory", 14},
		{"process managment issue", 24}
	};
	int type;

	write(STDERR_FILENO, globals.self.text, globals.self.length);
	write(STDERR_FILENO, ": ", 2);
	print_int(globals.line_num, STDERR_FILENO);
	write(STDERR_FILENO, ": ", 2);
	type = code & 0xF00;
	code &= 0x0FF;
	write(STDERR_FILENO, errors[code].text, errors[code].length);
	write(STDERR_FILENO, "\n", 1);
	if (type == 0x800)
		exit(code + 126);
	if (type == 0x400 && !globals.interactive)
		exit(code + 126);
}
