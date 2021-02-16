#include "command.h"
#include "libft.h"
#include "get_next_line.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

t_command	*command_create()
{
	t_command *command;

	command = ft_calloc(sizeof(t_command), 1);
	if (!command)
		return (NULL);
	if (command_read_input(command) < 1)
		return (NULL);
	command->argv = ft_split(command->input, ' ');
	if (!command->argv)
		return (NULL);
	command->code_error = 0;
	command->env = NULL;
	command->argc = 1;
	return(command);
}

int		command_read_input(t_command *_command)
{
	return (get_next_line(STDIN, &_command->input));
}

char 		*command_get_input(t_command *_command)
{
	return (_command->input);
}

void		command_execute(t_command *_command)
{
	pid_t	pid;
	int	status;

	pid = fork();
	if (pid == -1)
	{
		_command->code_error = errno;
		printf(strerror(errno));
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		if (execve(_command->argv[0], _command->argv, _command->env) == -1)
		{
			_command->code_error = errno;
			printf(strerror(errno));
			exit(EXIT_FAILURE);
		}
	}
}

int		command_get_code_error(t_command *_command)
{
	return (_command->code_error);
}

void		command_print_output(t_command *_command)
{
	printf("%s/n", _command->output);
}

void		command_destroy(t_command *_command)
{
	if (_command->input)
		free(_command->input);
	if (_command->output)
		free(_command->output);
	if (_command->argv)
		ft_destroy_array((void **)_command->argv, sizeof(char *), _command->argc);
	if (_command->env)
		free(_command->env);
	free(_command);
}
