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

t_pair	*env_pair_create_from_line(const char *line)
{
	t_pair	*pair;
	char	**split;

	split = ft_strsplit(line, '=');
	if (!split || ft_arraylen((const void **)split) != 2)
	{
		ft_array_destroy((void **)split, ft_arraylen((const void **)split));
		return (NULL);
	}
	pair = pair_create(split[0], split[1]);
	free(split);
	return (pair);
}

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
