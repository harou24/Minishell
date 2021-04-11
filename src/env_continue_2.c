#include <stdlib.h>

#include "debugger.h"
#include "libft.h"
#include "vector.h"
#include "environ.h"

#include "env.h"

void	*env_bootstrap_from_environ(const char **env)
{
	void	*hm_store;
	int		index;

	hm_store = hm_new(HASHMAP_SIZE);
	if (!hm_store)
		return (NULL);
	index = 0;
	while (env[index])
	{
		if (!env_insert_from_line(env[index], hm_store))
		{
			hm_destroy(hm_store, env_node_destroy_hm);
			return (NULL);
		}
		index++;
	}
	return (hm_store);
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

t_bool	env_add_to_environ(t_env_node *node, const char *key,
				char *value, e_scope scope)
{
	char	*line;

	if (scope == SCOPE_ENVIRON || node->scope == SCOPE_ENVIRON)
	{
		dbg("Adding key{%s}, value{%s} to environ!\n", key, value);
		line = ft_strjoin_multi(3, key, "=", value);
		if (node->environ_index >= 0)
		{
			if (!environ_set(node->environ_index, line))
				return (FALSE);
		}
		else
		{
			if (!environ_add(line))
				return (FALSE);
			node->environ_index = environ_size() - 1;
		}
		return (TRUE);
	}
	else
	{
		return (FALSE);
	}
}

t_bool	env_set(t_env *env, const char *key, char *value, e_scope scope)
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
	return (TRUE);
}
