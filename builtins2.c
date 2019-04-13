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
