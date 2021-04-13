#include <stdlib.h>

#include "libft.h"
#include "vector.h"
#include "environ.h"

#include "env.h"

t_env	*env_create(const char **environ)
{
	t_env	*this_env;

	this_env = ft_calloc(sizeof(t_env), 1);
	if (this_env)
	{
		this_env->hm_store = env_bootstrap_from_environ(environ);
		if (!this_env->hm_store)
			return (env_destroy(&this_env));
	}
	return (this_env);
}

t_env	*env_destroy(t_env **env)
{
	if (env)
	{
		if ((*env)->hm_store)
			hm_destroy((*env)->hm_store, env_node_destroy_hm);
		free(*env);
		*env = NULL;
	}
	return (NULL);
}
