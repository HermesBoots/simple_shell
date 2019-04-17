#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "common.h"


#define MIN(a, b) (a < b ? a : b)


/**
 * find_in_path - searches in PATH environment variable for argv[0]
 * @argv: argv array to be given to child process
 *
 * Return: Nothing?
 */
char find_in_path(char **argv)
{
	char empty_token = 0, *current;
	int code = ENOENT;
	size_t index;
	SubString tok;

	for (current = globals.path; *current != '\0'; current++)
	{
		if (*current == ':' && (*++current == ':' || *current == '\0'))
		{
			empty_token = 1;
			break;
		}
	}
	if (globals.path[0] == ':')
		empty_token = 1;
	tok = _strtok(globals.path, ":");
	while (tok.text != NULL)
	{
		index = _strncpy(globals.outbuf, tok.text, MIN(tok.length, 4097));
		if (index > 0 && globals.outbuf[index - 1] != '/')
			globals.outbuf[index++] = '/';
		index += _strncpy(globals.outbuf + index, argv[0], 4097 - index);
		errno = 0;
		if (access(globals.outbuf, F_OK) == 0)
		{
			execve(globals.outbuf, argv, collect_env());
			code = errno;
		}
		tok = _strtok(NULL, ":");
		if (empty_token && tok.text == NULL)
			tok.text = "", tok.length = 0, empty_token = 0;
	}
	errno = code;
	free(argv);
	if (errno == ENOENT || errno == ENOTDIR)
		error("not found");
	else
		error(NULL);
	free(globals.line);
	exit(globals.last_status);
}


/**
 * find_command - searches for path to argv[0]
 * @argv: argv array to be given to child process
 */
void find_command(char **argv)
{
	size_t index;

	errno = 0;
	for (index = 0; index < 4096 && argv[0][index] != '\0'; index++)
	{
		if (argv[0][index] == '/')
		{
			if (access(argv[0], F_OK) == 0)
			{
				execve(argv[0], argv, collect_env());
				free(argv);
				error(NULL);
				free(globals.line);
				exit(globals.last_status);
			}
			else
			{
				free(argv);
				error("not found");
				free(globals.line);
				exit(globals.last_status);
			}
		}
	}
	find_in_path(argv);
}


/**
 * run_program - Child finds program, if found executes program
 * @argv: the entire command line as broken up tokens
 */
void run_program(char **argv)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		find_command(argv);
	}
	else if (pid > 0)
	{
		wait(&status);
		globals.last_status = WEXITSTATUS(status);
	}
	else
	{
		error(NULL);
	}
}
