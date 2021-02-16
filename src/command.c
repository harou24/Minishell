#include "command.h"
#include "libft.h"
#include "get_next_line.h"
#include <stdlib.h>
#include <stdio.h>

t_command	*command_create(const char *_input)
{
	t_command *command;

	command = ft_calloc(sizeof(t_command), 1);
	if (!command)
		return (NULL);
	command->input = ft_strdup(_input);
	/*allocate command->output to store the result of command_execute() ??*/
	command->code_error = command_execute(command);
	return(command);
}

char		*command_get_input()
{
	char	*input;
	char	*line;
	int 	size;

	input = NULL;
	line = NULL;
	size = 0;
	while (get_next_line(stdin, &line) > 0)
	{
		size = ft_strlen(input) + ft_strlen(line);
		if (ft_realloc(input, 1, size))
			input = ft_strlcat(input, line, size);
	}
	return (input);
}

void		command_execute(t_command *_command)
{
	pid_t	pid;
	int	status;

	pid = fork();
	if (pid == -1)
	{
		_command->error_code = errno;
		printf(strerror(errno));
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		if (execve(_command->binary_path, _command->argv, _command->env) == -1)
		{
			_command->error_code = errno;
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
	if (_command->binary_path)
		free(_command->binary_path);
	if (_command->argv)
		ft_destroy_array(_command->argv, sizeof(char *), _command->argc);
	if (_command->env)
		free(_command->env);
	free(_command);
}
