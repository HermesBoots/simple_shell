#include <unistd.h>
#include "common.h"


void setup(int argc, char *argv[], char *envp[])
{
	int index = 0;
	char *path = "PATH=";
	int str_chk;

	while (argv[0][globals.self.length] != '\0')
		globals.self.length++;
	globals.self.text = argv[0];
	globals.line_num = 1;
	if (isatty(STDOUT_FILENO) == 1 && isatty(STDOUT_FILENO) == 1)
		globals.interactive = 1;
	while (envp[index] != NULL)
	{
		str_chk = _strncmp(envp[index], path, 5);
		if (str_chk == 1)
		{
			globals.path = envp[index];
			break;
		}
	}
}


int main(int argc __attribute__((unused)), char *argv[], char *envp[])
{
	setup(argc, argv, envp);
	return (globals.last_status);
}
