#include "bash_ops.h"
#include <stdio.h>
#include <stdlib.h>

void print_command(int argc, char **_argv)
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
	t_argv *argv = argv_create(argc + 1);
	int i = 1;

	while (i < argc)
	{
		argv_push(argv, _argv[i]);
		i++;
	}
	t_command *command = command_create(ft_strdup("echo"), argv);
	
	printf("--------echo test--------\n\n");
	printf("Command is ->");
	print_command(argc, _argv);
	builtin_echo(command);
	printf("\n-------------------------\n\n");
	exit(0);
/*	command_destroy(&command);*/
	return(0);
}
