#include <stdlib.h>

#include "environ.h"
#include "env_singleton.h"
#include "env.h"

t_env	*g_env__;

t_env	*env_init(char **env)
{
	if (g_env__)
		return (g_env__);
	g_env__ = env_create((const char **)env);
	if (g_env__)
	{
		if (!environ_init(env_to_array(g_env__, SCOPE_ENVIRON)))
			return (NULL);
	}
	return (g_env__);
}

void	env_deinit(t_env **env)
{
	if (g_env__)
		env_destroy(&g_env__);
	environ_deinit();
	if (env)
		*env = NULL;
	g_env__ = NULL;
}

char	*env_get_s(const char *key)
{
	return (env_get(g_env__, key));
}

t_bool	env_set_s(const char *key, char *value, e_scope scope)
{
	return (env_set(g_env__, key, value, scope));
}

t_bool	env_set_s_line(const char *line, e_scope scope)
{
	char	*key;
	char	*value;
	t_bool	succes;

	if (!ft_strchr(line, '='))
		return (FALSE);
	key = ft_strsub(line, 0, ft_strclen(line, '='));
	value = ft_strchr(line, '=') + 1;
	succes = env_set_s(key, value, scope);
	free(key);
	return (succes);
}
