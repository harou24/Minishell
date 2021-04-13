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
