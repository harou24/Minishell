#include "shell.h"
#include "libft.h"
#include "get_next_line.h"
#include "command.h"

t_shell	*shell_create(int _argc, char **_argv, char **_env)
{
	t_shell	*shell;

	shell = ft_calloc(sizeof(t_shell), 1);
	if (!shell)
		return (NULL);
	if (shell_read_input(shell) < 1)
		return (NULL);
	shell->env = get_env(_argc, _argv, _env);
	if (!shell->env)
		return (NULL);
	if (!shell->init_commands(shell))
		return (NULL);

}

char	**shell_get_env(int _argv, char **_argv, char **_env)
{
	char	**env;
	int	i;

	(void)_argc;
	(void)_argv;
	i = 0;
	env = (char**)malloc(sizeof(char *) * (ft_str_array_length(env) + 1)); /*need to update libft with ft_str_array_length()*/
	while (_env[i])
	{
		env[i] = ft_strdup(_env[i]);
		if (!env[i])
			return (NULL);
		i++;
	}
	return (env);
}

int	shell_read_input(t_command *_command)
{
	return (get_next_line(STDIN, &_shell->input));
}

int	shell_init_commands(t_shell *_shell)
{
	char	**split_input;
	int	i;

	split_input = ft_split(shell->input, ';');
	if (!split_input)
		return (0);
	_shell->nb_command = ft_str_array_length(split_input);
	_shell->commands = ft_calloc(sizeof(t_command), _shell->nb_command);
	if (!_shell->commands)
	{
		ft_destroy_array((void **)_command->argv, sizeof(void *), _shell->nb_command);
		return (0);
	}
	i = 0;
	while (i < _shell->nb_command)
	{
		commands[i] = command_create(split_input[i]);
		if (!command[i])
		{
			ft_destroy_array((void **)_command->argv, sizeof(void *), _shell->nb_command);
			return (0);
		}
		i++;
	}
	ft_destroy_array((void **)_command->argv, sizeof(void *), _shell->nb_command);
	return (1);
}

void	shell_destroy(t_shell *_shell)
{
	if (_shell->input)
		free(_shell->input)
	if (_shell->env)
		ft_destroy_array((void **)_command->argv, sizeof(void *), _shell->nb_command);
	if (shell->commands)
	{
		int i = 0;
		while (i < _shell->nb_commands)
		{
			command_destroy(_shell->command[i]);
			i++;
		}
	}
	free(_shell);
}
