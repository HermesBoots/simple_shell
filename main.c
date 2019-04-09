#include <errno.h>
#include <linux/limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "common.h"


/**
 * setup - initalising the global variables
 * @argc: number of arguments
 * @argv: array of strings
 * @envp: list of environment variables
 */
void setup(int argc __attribute__((unused)), char *argv[], char *envp[])
{
	int index = 0;
	char *path = "PATH=";
	int str_chk;

	signal(SIGINT, SIG_IGN);
	while (argv[0][globals.self.length] != '\0')
		globals.self.length++;
	globals.self.text = argv[0];
	globals.line_num = 1;
	if (isatty(STDOUT_FILENO) == 1 && isatty(STDIN_FILENO) == 1)
		globals.interactive = 1;
	while (envp[index] != NULL)
	{
		str_chk = _strncmp(envp[index], path, 5);
		if (str_chk == 0)
		{
			globals.path = envp[index];
			break;
		}
		index++;
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
int main(int argc __attribute__((unused)), char *argv[], char *envp[])
{
	char found;
	char **parsed;
	size_t size;
	ssize_t count;

	setup(argc, argv, envp);
	while (1)
	{
		errno = 0;
		if (globals.interactive)
			write(STDERR_FILENO, "$ ", 2);
		count = getline(&globals.line, &size, stdin);
		if (count < 1)
			break;
		parsed = parse(globals.line);
		if (parsed == NULL)
			continue;
		found = run_builtin(parsed, envp);
		if (!found)
			run_program(parsed, envp);
		globals.line_num++;
		free(parsed);
	}
	if (errno == 0 && globals.interactive)
		write(STDERR_FILENO, "\n", 1);
	else
		error(NULL);
	free(globals.line);
	return (globals.last_status);
}
