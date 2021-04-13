#include <stdlib.h>

#include "environ.h"
#include "env_singleton.h"
#include "env.h"

extern t_env	*g_env__;

char	*env_get_s(const char *key)
{
	return (env_get(g_env__, key));
}

t_bool	env_set_s(const char *key, char *value, e_scope scope)
{
	return (env_set(g_env__, key, value, scope));
}

t_bool	env_unset_s(const char *key)
{
	if (g_env__)
		env_unset(g_env__, key);
	return (TRUE);
}

char	**env_to_array_s(e_scope scope)
{
	return (env_to_array(g_env__, scope));
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
