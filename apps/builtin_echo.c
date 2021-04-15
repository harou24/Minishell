#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bash_ops.h"

void print_command(int argc, const char **_argv)
{
	int i = 1;
	while (i < argc)
	{
		printf("%s ",_argv[i]);
		i++;
	}
	printf("\n");
}

int main(int argc, char **_argv)
{
	const char *path = "/bin/path";

	t_argv *argv = argv_create(strdup(path));

	int i = 1;
	while (i < argc)
	{
		argv_push(argv, _argv[i]);
		i++;
	}
	t_command *command = command_create(ft_strdup("path"));
	
	printf("--------echo test--------\n\n");
	printf("Command is ->");
	print_command(argv_get_size(argv), argv_get_array(argv));
	builtin_echo(command);
	printf("\n-------------------------\n\n");
	command_destroy(&command);
	argv_destroy(&argv);
	return(0);
}
