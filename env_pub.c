#include <stdlib.h>
#include "common.h"
#include "env.h"

/**
 * update_env - Update an evironment variable
 * @name: name of variable to update
 * @val: value to update variable to
 */
void update_env(char *name, char *val)
{
	ShellVar *node;
	size_t length;
	unsigned int ivar;

	ivar = find_env(name);
	if (ivar == NOT_FOUND)
	{
		node = new_env();
		add_env(node, name, val);
		free(env.envp);
		env.envp = NULL;
		return;
	}
	node = &env.arr[ivar];
	for (length = 0; val[length] != '\0'; length++)
		;
	if (length > node->val->length)
	{
		node->capacity *= 2;
		node->name = _realloc(node->name, node->capacity);
		if (node->name == NULL)
			error(NULL);
		node->val = node->name + 1;
		node->name->text = (char *)(node->val + 1);
		node->val->text = node->name->text + node->name->length + 1;
	}
	node->val->length = length;
	_memcpy(node->val->text, val, length);
	node->val->text[length] = '\0';
	free(env.envp);
	env.envp = NULL;
	if (_strncmp(name, "PATH", 4) == 0)
		globals.path = node->val->text;
}

/**
 * del_env - deletes an environment variable
 * @name: name of variable to delete
 *
 * Return: 0 on failure, 1 on success
 */
int del_env(char *name)
{
	unsigned int ivar;

	ivar = find_env(name);
	if (ivar == NOT_FOUND)
		return (0);
	free(env.arr[ivar].name);
	for (; ivar < env.count - 1; ivar++)
		_memcpy(
			(void *)&env.arr[ivar],
			(void *)&env.arr[ivar + 1],
			sizeof(ShellVar)
		);
	env.count--;
	free(env.envp);
	env.envp = NULL;
	return (1);
}

/**
 * init_environ - initializing our new copy of envp
 * @envp: argument ot main/original environment variable
 */
void init_environ(char **envp)
{
	size_t i;

	for (env.count = 0; envp[env.count] != NULL; env.count++)
		;
	env.capacity = env.count;
	env.arr = malloc(sizeof(ShellVar) * env.count);
	if (env.arr == NULL)
		error(NULL);
	for (env.count = 0; envp[env.count] != NULL; env.count++)
	{
		for (i = 0; envp[env.count][i] != '='; i++)
			;
		envp[env.count][i++] = '\0';
		add_env(&env.arr[env.count], envp[env.count], &envp[env.count][i]);
		if (_strncmp(env.arr[env.count].name->text, "PATH", 4) == 0)
			globals.path = env.arr[env.count].val->text;
	}
}

/**
 * collect_env - copying env array into our own envp
 *
 * Return: cached envp or new envp
 */
char **collect_env(void)
{
	unsigned int count;

	if (env.envp != NULL)
		return (env.envp);
	env.envp = malloc(sizeof(char *) * (env.count + 1));
	if (env.envp == NULL)
		error(NULL);
	for (count = 0; count < env.count; count++)
		env.envp[count] = env.arr[count].name->text;
	env.envp[count] = NULL;
	return (env.envp);
}

/**
 * done_environ - Free the memory we allocated for our env struct
 */
__attribute__((destructor))
void done_environ(void)
{
	unsigned int index;

	free(env.envp);
	if (env.arr != NULL)
	{
		for (index = 0; index < env.count; index++)
			free(env.arr[index].name);
	}
	free(env.arr);
}
