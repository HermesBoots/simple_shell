#include <stdlib.h>
#include "common.h"
#include "env.h"

/**
 * find_env - Find string inside env
 * @name: Name of env string to find
 *
 * Return: index of env variable or NOT_FOUND
 */
unsigned int find_env(char *name)
{
	unsigned int ivar;
	size_t ichar;
	char *other;

	for (ivar = 0; ivar < env.count; ivar++)
	{
		ichar = 0;
		other = env.arr[ivar].name->text;
		while (name[ichar] != '\0' && other[ichar] != '\0')
		{
			if (name[ichar] != other[ichar])
				break;
			ichar++;
		}
		if (name[ichar] == '\0' && other[ichar] == '=')
			return (ivar);
	}
	return (NOT_FOUND);
}

/**
 * new_env - Setup for adding a new env variable. realloc more space if needed.
 *
 * Return: pointer to newly allocated variable
 */
ShellVar *new_env()
{
	if (env.count == env.capacity)
	{
		env.capacity *= 2;
		env.arr = _realloc(env.arr, sizeof(ShellVar) * env.capacity);
		if (env.arr == NULL)
			error(NULL);
	}
	return (&env.arr[env.count++]);
}

/**
 * add_env - Add a new env variable
 * @node: Struct for entire new env variable
 * @name: Name of the new variable ie. "PATH"
 * @val: Value of new variable ie "/bin/usr"
 */
void add_env(ShellVar *node, char *name, char *val)
{
	size_t name_len, val_len;

	for (name_len = 0; name[name_len] != '\0'; name_len++)
		;
	for (val_len = 0; val[val_len] != '\0'; val_len++)
		;
	node->capacity = sizeof(SubString) * 2 + name_len + val_len + 2;
	node->name = malloc(node->capacity);
	if (node->name == NULL)
		error(NULL);
	node->val = node->name + 1;
	node->name->length = name_len;
	node->name->text = (char *)(node->val + 1);
	_memcpy(node->name->text, name, name_len);
	node->name->text[name_len] = '=';
	node->val->length = val_len;
	node->val->text = node->name->text + name_len + 1;
	_memcpy(node->val->text, val, val_len);
	node->val->text[val_len] = '\0';
}
