#include <assert.h>
#include <stdlib.h>

#include "environ.h"
#include "env_singleton.h"

static t_env *g_env__;

t_env		*env_init(char **env)
{
	if (g_env__)
		return(g_env__);
	g_env__ = env_create((const char **)env);
	if (g_env__)
	{
		assert(environ_init(env_to_array(g_env__, SCOPE_ENVIRON)));
	}
	return (g_env__);
}

void		env_deinit(t_env **env)
{
	if (g_env__)
		env_destroy(g_env__);
	environ_deinit();
	if (env)
		*env = NULL;
	g_env__ = NULL;
}

char		*env_get_s(const char *key)
{
	assert(g_env__);
	return (env_get(g_env__, key));
}

t_bool		env_set_s(const char *key, char *value, e_scope scope)
{
	assert(g_env__);
	return (env_set(g_env__, key, value, scope));
}

t_bool		env_unset_s(const char *key)
{
	assert(g_env__);
	if (g_env__)
		env_unset(g_env__, key);
	return (TRUE); /* env.h doesn't provide error handling for unset */
}
