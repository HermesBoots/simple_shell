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
	while (argv[0][globals.self_len] != '\0')
		globals.self_len++;
	_strncpy(globals.self, argv[0], 4096);
	globals.line_num = 1;
	if (isatty(STDOUT_FILENO) == 1 && isatty(STDOUT_FILENO) == 1)
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
	char **parsed;
	int i = 0;

	setup(argc, argv, envp);
	parsed = parse(argv[1]);
	while (parsed[i] != NULL)
	{
		printf("argv[%d]: %s\n", i, parsed[i]);
		i++;
	}
	printf("found? %s\n", find_command(parsed) ? "true" : "false");
	printf("command: %s\n", globals.command);
	free(parsed);
	return (0);
}
