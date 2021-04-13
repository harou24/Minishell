#include <stdlib.h>

#include "libft.h"
#include "vector.h"
#include "environ.h"

#include "env.h"

t_bool	env_unset(t_env *env, const char *key)
{
	t_env_node	*node;

	if (!env_get_node_for_key(env, key))
		return (FALSE);
	node = env_get_node_for_key(env, key);
	if (node->environ_index >= 0)
		environ_remove(node->environ_index);
	hm_remove(env->hm_store, key, env_node_destroy_hm);
	return (TRUE);
}

t_bool	env_set(t_env *env, const char *key, char *value, t_scope_e scope)
{
	t_env_node	*node;

	node = hm_get(env->hm_store, key);
	if (node)
	{
		if (node->value != value)
		{
			free(node->value);
			node->value = ft_strdup(value);
		}
	}
	else
	{
		node = env_node_create(key, value, scope);
		hm_set(env->hm_store, key, node);
	}
	env_add_to_environ(node, key, value, scope);
	if (scope == SCOPE_ENVIRON)
		env_set(env, key, value, SCOPE_LOCAL);
	return (TRUE);
}

char	*env_get(t_env *env, const char *key)
{
	t_env_node	*node;

	node = env_get_node_for_key(env, key);
	if (node != NULL)
		return (node->value);
	else
		return (NULL);
}

size_t	env_size(t_env *env)
{
	return (hm_size(env->hm_store));
}

char	**env_to_array(t_env *env, t_scope_e scope)
{
	char		**environ;
	size_t		index;
	size_t		count;
	t_env_node	*node;

	hm_get_seq(NULL);
	environ = (char **)ft_calloc(sizeof(char *), env_size(env) + 1);
	if (!environ)
		return (NULL);
	index = 0;
	count = 0;
	while (count < env_size(env))
	{
		node = env_get_next_node(env);
		if (node && node->scope == scope)
		{
			environ[index] = ft_strjoin_multi(3, node->key, "=", node->value);
			node->environ_index = index;
			index++;
		}
		count++;
	}
	return (environ);
}
