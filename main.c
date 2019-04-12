#include <errno.h>
#include <fcntl.h>
#include <linux/limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "common.h"


/**
 * sigint_handler - handle the Ctrl+C signal
 * @sig: signal number, always the same so ignored
 */
void sigint_handler(int sig __attribute__((unused)))
{
	write(STDERR_FILENO, "\n$ ", 3);
}


/**
 * setup - initalising the global variables
 * @argc: number of arguments
 * @argv: array of strings
 * @envp: list of environment variables
 */
void setup(int argc, char *argv[], char *envp[])
{
	int index = 0;
	char *path = "PATH=";

	globals.self.text = argv[0];
	while (argv[0][globals.self.length] != '\0')
		globals.self.length++;
	if (argc > 1)
	{
		globals.input = open(argv[1], O_RDONLY);
		if (globals.input < 0)
		{
			_strncpy(globals.outbuf, argv[0], globals.self.length);
			_strncpy(globals.outbuf + globals.self.length, ": 0: ", 5);
			write(STDERR_FILENO, globals.outbuf, globals.self.length + 5);
			for (; argv[1][index] != '\0'; index++)
				;
			write(STDERR_FILENO, "Can't open ", 11);
			write(STDERR_FILENO, argv[1], index);
			write(STDERR_FILENO, "\n", 1);
			exit(127);
		}
	}
	else
	{
		globals.input = STDIN_FILENO;
	}
	if (isatty(STDOUT_FILENO) == 1 && isatty(globals.input) == 1)
	{
		globals.interactive = 1;
		signal(SIGINT, &sigint_handler);
	}
	globals.path = "";
	for (; envp[index] != NULL; index++)
	{
		if (_strncmp(envp[index], path, 5) == 0)
			globals.path = envp[index];
	}
}


/**
 * main - starts thew shell
 * @argc: number of arguments
 * @argv: array of strings
 * @envp: list of environment variables
 *
 * Return: A specified exit code or status of last command
 */
int main(int argc, char *argv[], char *envp[])
{
	char found;
	char **parsed;
	size_t size;
	ssize_t count = 0;

	setup(argc, argv, envp);
	while (1)
	{
		errno = 0;
		if (globals.interactive)
			write(STDERR_FILENO, "$ ", 2);
		count = _getline(&globals.line, &size, globals.input);
		globals.line_num++;
		if (count < 1)
			break;
		parsed = parse(globals.line);
		if (parsed == NULL)
			continue;
		found = run_builtin(parsed, envp);
		if (!found)
			run_program(parsed, envp);
		free(parsed);
	}
	if (errno == 0 && globals.interactive)
		write(STDERR_FILENO, "\n", 1);
	else
		error(NULL);
	free(globals.line);
	return (globals.last_status);
}
