#ifndef _COMMON_H_
#define _COMMON_H_

#include <stddef.h>
#include <stdint.h>


/**
 * struct SubString - enabling passing strings along with their lengths
 * @text: pointer to first byte in substring
 * @length: length of substring
 */
typedef struct SubString
{
	char *text;
	size_t length;
} SubString;


/**
 * struct ShellGlobals - stores state of the shell that many functions need
 * @line: buffer for current input line
 * @self_len: length of self string
 * @command: the name of / path to the command being executed
 * @path: the current executable search path
 * @last_status: exit status of previous command
 * @line_num: which input line is being executed
 * @interactive: whether this shell is in interactive mode
 * @self: the original argv[0]
 */
struct ShellGlobals
{
	size_t self_len;
	char *line;
	char *path;
	int last_status;
	uint32_t line_num;
	char interactive;
	char command[4109];
	char self[4120];
} globals;


void error(char *command);
int _strncmp(char const *s1, char const *s2, size_t n);
size_t _strncpy(char *dest, char const *src, size_t count);
void _memcpy(char *dest, char const *src, size_t count);
size_t print_int(char *buffer, int64_t val);
SubString _strtok(char *str, char const *delim);
char **parse(char *str);
char find_command(char **argv);
void run_program(char **argv, char **envp);


#endif
