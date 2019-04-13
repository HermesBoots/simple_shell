#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "common.h"


#include "builtins2.c"


/**
 * builtin_exit - exits the shell
 * @argv: pointer to tokenized command line string
 * @envp: pointer to environment variable
 *
 * Return: 2 or exit the shell
 */
int builtin_exit(char **argv, char **envp __attribute__((unused)))
{
	static int const max = 2147483647;
	char *sub;
	int code = 0;
	unsigned int index;

	if (argv[1] == NULL)
	{
		free(argv);
		free(globals.line);
		exit(globals.last_status);
	}
	for (sub = argv[1]; *sub != '\0'; sub++)
	{
		if (max / 10 < code || *sub < '0' || *sub > '9')
			break;
		code *= 10;
		if (max - *sub - '0' < code)
			break;
		code += *sub - '0';
	}
	if (*sub == '\0')
	{
		free(argv);
		free(globals.line);
		exit(code);
	}
	errno = ENOTDIR;
	index = argv[1][0];
	sub = argv[0] - 11;
	_strncpy(sub, "Illegal number: ", 16);
	sub[16] = index;
	error(sub);
	return (2);
}


/**
 * builtin_env - creating the BUILT-IN envp variable for our shell
 * @argv: pointer to tokenized command line string
 * @envp: pointer to environment variable
 *
 * Return: 0;
 */
int builtin_env(char **argv __attribute__((unused)), char **envp)
{
	unsigned int index;
	size_t length;

	for (index = 0; envp[index] != NULL; index++)
	{
		for (length = 0; envp[index][length] != '\0'; length++)
			;
		write(STDOUT_FILENO, envp[index], length);
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}


int builtin_help(char **argv, char **envp __attribute__((unused)))
{
#include "help_pages.def"
	static char const *commands[] = {"cd", "env", "exit", "help", "setenv",
		"unsetenv"};
	static char const *pages[] = {help_cd, help_env, help_exit, help_help,
		help_setenv, help_unsetenv};
	static unsigned int const count = 6;
	static size_t const max = 8;
	unsigned int i;

	if (argv[1] == NULL)
	{
		write(STDOUT_FILENO, help_general, len_general);
		return (0);
	}
	for (i = 0; i < count; i++)
	{
		if (_strncmp(commands[i], argv[1], max) == 0)
		{
			write(STDOUT_FILENO, pages[i], lengths[i]);
			return (0);
		}
	}
	_strncpy(globals.outbuf, globals.self.text, globals.self.length);
	_strncpy(globals.outbuf + globals.self.length,
		": help: no help topics match `", 30);
	write(STDERR_FILENO, globals.outbuf, globals.self.length + 30);
	for (i = 0; argv[1][i] != '\0'; i++)
		;
	write(STDERR_FILENO, argv[1], i);
	write(STDERR_FILENO, "'.\n", 3);
	return (1);
}


/**
 * run_builtin - run the builtin commands we implemented
 * @argv: pointer to a tokenized array of strings
 *
 * Return: 1 on success, 0 on failure
 */
char run_builtin(char **argv)
{
	static builtin functions[] = {NULL, &builtin_env, &builtin_exit,
		&builtin_help, &builtin_setenv, &builtin_unsetenv};
	static char const *commands[] = {"cd", "env", "exit", "help", "setenv",
		"unsetenv"};
	static unsigned int const count = 6;
	static size_t const max = 8;
	unsigned int i;

	for (i = 0; i < count; i++)
	{
		if (_strncmp(commands[i], argv[0], max) == 0)
		{
			globals.last_status = functions[i](argv, collect_env());
			return (1);
		}
	}
	return (0);
}
