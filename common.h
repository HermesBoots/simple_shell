#ifndef _COMMON_H_
#define _COMMON_H_

#include <stddef.h>
#include <stdint.h>
#include <unistd.h>


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
 * struct ShellVar - stores the information needed for shell environment vars
 * @capacity: number of bytes allocated outside this struct to store the var
 * @name: variable name
 * @val: variable value
 */
typedef struct ShellVar
{
	size_t capacity;
	SubString *name;
	SubString *val;
} ShellVar;


/**
 * struct ShellGlobals - stores state of the shell that many functions need
 * @command: first word of command line
 * @self: the original argv[0]
 * @line: buffer for current input line
 * @path: the current executable search path
 * @input: file descriptor to read commands from
 * @last_status: exit status of previous command
 * @line_num: which input line is being executed
 * @interactive: whether this shell is in interactive mode
 * @outbuf: buffer used to store path to command and error output
 */
struct ShellGlobals
{
	SubString command;
	SubString self;
	char *line;
	char *path;
	int input;
	int last_status;
	uint32_t line_num;
	char interactive;
	/*
	 * MAX_PATH (4096) for argv[0] +
	 * 20 for length of INT64_MIN as a string
	 * 4 for the two ": " separators
	 */
	char outbuf[4120];
} globals;


typedef int (*builtin)(char **, char **);


void error(char *command);
int _strncmp(char const *s1, char const *s2, size_t n);
size_t _strncpy(char *dest, char const *src, size_t count);
void _memcpy(char *dest, char const *src, size_t count);
size_t print_int(char *buffer, int64_t val);
SubString _strtok(char *str, char const *delim);
char **parse(char *str);
char run_builtin(char **argv);
void run_program(char **argv);
ssize_t _getline(char **line, size_t *size, int fd);
void *_realloc(void *ptr, size_t size);
void init_environ(char **envp);
void update_env(char *name, char *val);
char **collect_env(void);
int del_env(char *name);


#endif
