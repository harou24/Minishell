#include "shell.h"
#include "libft.h"
#include "env_access.h"

t_shell	*shell_create(const char **_env)
{
	t_shell *shell;

	shell = ft_calloc(sizeof(t_shell), 1);
	if (!shell)
		return (NULL);
	shell->env = env_create(_env);
	shell->prompt = prompt_create(env_get_user(), env_get_host());
	if (!shell->env || !shell->prompt)
	{
		shell_destroy(shell);
		return (NULL);
	}
	return (shell);
}

void	shell_destroy(t_shell *_shell)
{
	if (_shell->env)
		env_destroy(_shell->env);
	if (_shell->prompt)
		prompt_destroy(_shell->prompt);
	free(_shell);
}
