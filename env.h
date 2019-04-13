#ifndef _ENV_H_
#define _ENV_H_

#include <limits.h>
#include "common.h"


#define NOT_FOUND UINT_MAX


/**
 * struct Environment - structure to represent shell's whole environment
 * @capacity: number of variables allocated
 * @count: number of variables in use
 * @envp: cached envp to be passed to child processes
 * @arr: array of shell variables
 */
struct Environment
{
	unsigned int capacity;
	unsigned int count;
	char **envp;
	ShellVar *arr;
} env;


unsigned int find_env(char *name);
ShellVar *new_env(void);
void add_env(ShellVar *node, char *name, char *val);


#endif
