#include "libft.h"
#include "vector.h"
#include "environ.h"

#include "env.h"

t_env_node	*env_get_node_for_key(t_env *env, const char *key)
{
	return ((t_env_node *)hm_get(env->hm_store, key));
}

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

size_t	env_size(t_env *env)
{
	return (hm_size(env->hm_store));
}

t_env_node	*get_next_env_node(t_env *env)
{
	t_pair	pair;

	pair = hm_get_seq(env->hm_store);
	return ((t_env_node *)pair.s.value);
}

char	**env_to_array(t_env *env, e_scope scope)
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
		node = get_next_env_node(env);
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
