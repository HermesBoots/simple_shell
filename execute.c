#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "common.h"


#define MIN(a, b) (a < b ? a : b)


/**
 * find_in_path - searches in PATH environment variable for argv[0]
 * @argv: argv array to be given to child process
 * @envp: pointer to environment variables
 *
 * Return: Nothing?
 */
char find_in_path(char **argv, char **envp)
{
	int code = ENOENT;
	size_t index;
	SubString tok;

	tok = _strtok(globals.path, ":");
	while (tok.text != NULL)
	{
		index = _strncpy(globals.outbuf, tok.text, MIN(tok.length, 4097));
		if (globals.outbuf[index - 1] != '/')
			globals.outbuf[index++] = '/';
		index += _strncpy(globals.outbuf + index, argv[0], 4097 - index);
		errno = 0;
		if (access(globals.outbuf, F_OK) == 0)
		{
			execve(globals.outbuf, argv, envp);
			code = errno;
		}
		tok = _strtok(NULL, ":");
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
 * @envp: pointer to environment variables
 */
void find_command(char **argv, char **envp)
{
	size_t index;

	errno = 0;
	for (index = 0; index < 4096 && argv[0][index] != '\0'; index++)
	{
		if (argv[0][index] == '/')
		{
			if (access(argv[0], F_OK) == 0)
			{
				execve(argv[0], argv, envp);
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
	find_in_path(argv, envp);
}


/**
 * run_program - Child finds program, if found executes program
 * @argv: the entire command line as broken up tokens
 * @envp: pointer to environment variables
 */
void run_program(char **argv, char **envp)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		find_command(argv, envp);
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
