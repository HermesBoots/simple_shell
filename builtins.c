#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "common.h"


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


char run_builtin(char **argv, char **envp)
{
	static builtin functions[2] = {&builtin_exit, &builtin_env};
	static char *commands[] = {"exit", "env"};
	static unsigned int const count = 2;
	static size_t const max = 4;
	unsigned int i;

	for (i = 0; i < count; i++)
	{
		if (_strncmp(commands[i], argv[0], max) == 0)
		{
			globals.last_status = functions[i](argv, envp);
			return (1);
		}
	}
	return (0);
}
