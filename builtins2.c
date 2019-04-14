#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "common.h"


/**
 * builtin_setenv - add or update an environment variable
 * @argv: array of command-line arguments
 * @envp: unused, this function uses the env*.c functions instead
 *
 * Return: 2 if not enough arguments, otherwise 0
 */
int builtin_setenv(char **argv, char **envp __attribute__((unused)))
{
	if (argv[1] == NULL || argv[2] == NULL)
	{
		errno = ENOEXEC;
		error("Usage: setenv NAME VALUE");
		return (2);
	}
	update_env(argv[1], argv[2]);
	return (0);
}


/**
 * builtin_unsetenv - delete an environment variable
 * @argv: array of command-line arguments
 * @envp: unused
 *
 * Return: 2 if no variable named or name matches no variables, otherwise 0
 */
int builtin_unsetenv(char **argv, char **envp __attribute__((unused)))
{
	if (argv[1] == NULL)
	{
		errno = ENOEXEC;
		error("Usage, unsetenv NAME");
		return (2);
	}
	if (!del_env(argv[1]))
	{
		errno = ENOENT;
		error("Variable not found");
		return (2);
	}
	return (0);
}

/**
 * cd_loop - loop to run through envp and check for a match to a str
 * @str: string to check for
 * @len: length of the string to check
 * @envp: point to the environment variable
 *
 * Return: a pointer to the end of the found string, or "." if not found
 */
char *cd_loop(char *str, int len, char **envp)
{
	unsigned int i;

	for (i = 0; envp[i] != NULL; i++)
	{
		if (_strncmp(str, envp[i], len) == 0)
			return (envp[i] + len);
	}
	return (".");
}

/**
 * builtin_cd - builtin to change your current working directory
 * @argv: pointer to the command entered
 * @envp: pointer to the environment variable
 *
 * Return: 0 for success, 2 for failure
 */
int builtin_cd(char **argv, char **envp)
{
	char *buff = NULL;
	unsigned int i;

	errno = 0;
	if (argv[1] == NULL)
	{
		argv[1] = cd_loop("HOME=", 5, envp);
	}
	else if (argv[1][0] == '-' && argv[1][1] == '\0')
	{
		argv[1] = cd_loop("OLDPWD=", 7, envp);
		for (i = 0; argv[1][i] != '\0'; i++)
			;
		write(STDOUT_FILENO, argv[1], i);
		write(STDOUT_FILENO, "\n", 1);
	}
	if (chdir(argv[1]) != 0)
	{
		_strncpy(argv[0] - 9, "can't cd to", 11);
		argv[0][2] = ' ';
		error(argv[0] - 9);
		return (2);
	}
	for (i = 0; envp[i] != NULL; i++)
	{
		if (_strncmp("PWD=", envp[i], 4) == 0)
		{
			update_env("OLDPWD", envp[i] + 4);
			buff = getcwd(NULL, 0);
			if (buff == NULL)
				error(NULL);
			update_env("PWD", buff);
			free(buff);
			break;
		}
	}
	return (0);
}
