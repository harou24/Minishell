#include <assert.h>
#include <stdlib.h>

#include "libft.h"

#include "env_singleton.h"

static t_env *g_env__;

t_env		*env_init(char **env)
{
	if (g_env__)
		return(g_env__);
	g_env__ = env_create((const char **)env);
	return (g_env__);
}

void		env_deinit()
{
	if (g_env__)
		env_destroy(g_env__);
	g_env__ = NULL;
}

void		*env_get_s(const char *key)
{
	assert(g_env__);
	return (env_get(g_env__, (char *)key)); /* env.h: API -> const */
	
}

t_bool		env_set_s(const char *key, void *value)
{
	if (g_env__)
	{
		return (env_set(g_env__, (char *)key, value) != NULL); /* env.h: API -> const */
	}
	return (FALSE);
}

t_bool		env_unset_s(const char *key)
{
	if (g_env__)
		env_unset(g_env__, (char *)key); /* env.h: API -> const */
	return (TRUE); /* env.h doesn't provide error handling for unset */
}
