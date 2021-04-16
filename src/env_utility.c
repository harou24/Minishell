#include <stdlib.h>

#include "libft.h"
#include "vector.h"
#include "environ.h"

#include "env.h"

t_env_node	*env_node_create_from_line(const char *line)
{
	t_env_node	*node;
	int			equal_sign_index;
	char		*key;
	char		*value;

	equal_sign_index = ft_strclen(line, '=');
	key = ft_strsub(line, 0, equal_sign_index);
	value = ft_strchr(line, '=') + 1;
	node = env_node_create(key, value, SCOPE_ENVIRON);
	if (!key || !value || !node)
	{
		env_node_destroy(&node);
		node = NULL;
	}
	free(key);
	return (node);
}

t_bool	env_insert_from_line(const char *envline, void *hm_store)
{
	t_env_node	*node;

	node = env_node_create_from_line(envline);
	if (!node || !hm_set(hm_store, node->key, node))
		return (FALSE);
	return (TRUE);
}

t_env_node	*env_get_node_for_key(t_env *env, const char *key)
{
	return ((t_env_node *)hm_get(env->hm_store, key));
}

t_env_node	*env_get_next_node(t_env *env)
{
	t_pair	pair;

	pair = hm_get_seq(env->hm_store);
	return ((t_env_node *)pair.u_s.value);
}
