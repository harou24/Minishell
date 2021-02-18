#include "command.h"
#include "libft.h"
#include "get_next_line.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

t_command	*command_create(const char *_input)
{
	t_command *command;

	command->input = ft_strdup(_input);
	if (!command->input)
		return (NULL);
	command = ft_calloc(sizeof(t_command), 1);
	if (!command)
		return (NULL);
	command->argv = ft_split(command->input, ' ');
	if (!command->argv)
		return (NULL);
	command->code_error = 0;
	command->argc = ft_str_array_length();
	return(command);
}

void		command_execute(t_command *_command, char **_env)
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
		if (execve(_command->argv[0], _command->argv, _env) == -1)
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

void		command_destroy(t_command *_command)
{
	if (_command->input)
		free(_command->input);
	if (_command->output)
		free(_command->output);
	if (_command->argv)
		ft_destroy_array((void **)_command->argv, sizeof(void*), _command->argc);
	if (_command->env)
		free(_command->env);
	free(_command);
}

int		command_run_builtins(t_command *_command)
{
	if (ft_strcmp(_command->argv[0], "echo") == 0)
		return (command_run_echo(_command));
	if (ft_strcmp(_command->argv[0], "cd") == 0)
		return (command_run_cd(_command));
	if (ft_strcmp(_command->argv[0], "pwd") == 0)
		return (command_run_pwd(_command));
	if (ft_strcmp(_command->argv[0], "export") == 0)
		return (command_run_export(_command));
	if (ft_strcmp(_command->argv[0], "env") == 0)
		return (command_run_env(_command));
	if (ft_strcmp(_command->argv[0], "exit") == 0)
		return (command_run_exit(_command));
	return (0);
}

int	command_run_echo(t_command *_command)
{
	return (0);
}

int	command_run_cd(t_command *_command)
{
	return (0);
}

int	command_run_pwd(t_command *_command)
{
	return (0);
}

int	command_run_unset(t_command *_command)
{
	return (0);
}

int	command_run_export(t_command *_command)
{
	return (0);
}

int	command_run_env(t_command *_command)
{
	return (0);
}

int	command_run_exit(t_command *_command)
{
	return (0);
}
