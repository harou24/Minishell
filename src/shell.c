#include "shell.h"
#include "libft.h"
#include <stdlib.h>

t_shell		*shell_create(const char *_username, const char *_hostname)
{
	t_shell	*shell;

	shell = ft_calloc(sizeof(t_shell), 1);
	if (!shell)
		return (NULL);
	shell->prompt = prompt_create(_username, _hostname);
	if (!shell->prompt)
		return (NULL);
	shell->hm_env = shell_get_env();
	if (!shell->hm_env)
		return (NULL);
	return (shell);
}

void	*shell_get_env(void)
{
	extern char	**environ;
	char 		**_env = environ;
	void		*env;
	char		*key=NULL;
	char		*value=NULL;
	int		i;

	env = hm_new(ft_arraylen((const void **)_env));
	if (!env)
		return (NULL);
	i = 0;
	while (_env[i])
	{
		int equal_sign = ft_strclen(_env[i], '=');
		key = ft_strsub(_env[i], 0, equal_sign);
		value = ft_strsub(_env[i], equal_sign + 1, ft_strlen(_env[i]) - equal_sign);
		hm_set(env, key, value);
		i++;
	}
	return (env);
}

void		shell_destroy(t_shell *_shell)
{
	if (_shell->prompt)
		prompt_destroy(_shell->prompt);
	if (_shell->hm_env)
		hm_destroy(_shell->hm_env);
	free(_shell);
}
