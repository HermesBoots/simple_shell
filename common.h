#ifndef _COMMON_H_
#define _COMMON_H_

#include <stddef.h>
#include <stdint.h>
#include "errors.h"


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


/**
 * struct ShellGlobals - stores state of the shell that many functions need
 * @self: the original argv[0]
 * @command: the name of / path to the command being executed
 * @line: the text of the line being executed
 * @path: the current executable search path
 * @last_status: exit status of previous command
 * @line_num: which input line is being executed
 * @interactive: whether this shell is in interactive mode
 */
struct ShellGlobals
{
	SubString self;
	char const *command;
	char const *line;
	char const *path;
	int last_status;
	uint32_t line_num;
	char interactive;
} globals;


int _strncmp(char const *s1, char const *s2, size_t n);
void _memcpy(char *dest, char const *src, size_t count);
void print_int(int64_t val, int fd);
SubString _strtok(char const *str, char const *delim);


#endif
