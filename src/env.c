#include "libft.h"
#include "env.h"
#include <stdlib.h>

#define HASHMAP_SIZE 1000

size_t	g_environ_size = 128;

t_pair	*pair_create_from_line(const char *line)
{
	t_pair		*pair;
	int		equal_sign_index;
	char		*key;
	t_env_node	*value;

	equal_sign_index = ft_strclen(line, '=');
	key = ft_strsub(line, 0, equal_sign_index);
	value = env_node_create(line, ENVIRON);
	pair = pair_create(key, value);
	if (!pair)
	{
		pair_destroy(pair);
		return (NULL);
	}
	return (pair);
}

int	env_instert_from_line(t_env *env, const char *envline, void *hm_store)
{
	t_pair	*pair;

	pair = pair_create_from_line(envline);
	if (!pair || !hm_set(hm_store, pair->f.key, pair->s.value))
	{
		free(pair->f.key);
		env_destroy(env);
		return (0);
	}
	free(pair->f.key);
	pair_destroy(pair);
	return (1);
}

void	*env_bootstrap_from_environ(t_env *this_env, const char **env)
{
	void		*hm_store;
	int		count;

	hm_store = hm_new(HASHMAP_SIZE);
	if (!hm_store)
		return (NULL);
	count = 0;
	while(env[count])
	{
		if (!env_instert_from_line(this_env, env[count], hm_store))
			return (NULL);
		count++;
	}
	return (hm_store);
}


t_env	*env_create(const char **env)
{
	t_env	*this_env;

	this_env = ft_calloc(sizeof(t_env), 1);
	if (!this_env)
		return (NULL);
	this_env->store_size = ft_arraylen((const void**)env);
	this_env->hm_store = env_bootstrap_from_environ(this_env, env);
	if (!this_env->hm_store)
		return (NULL);
	return (this_env);
}

char	*env_get(t_env *env, const char *key)
{
	return ((char *)hm_get(env->hm_store, key));
}

void	*env_set(t_env *env, const char *key, char *value)
{
	return (hm_set(env->hm_store, key, value));
}

t_env_node	*env_get_node_for_key(t_env *env, const char *key)
{
	t_env_node *node = (t_env_node *)hm_get(env->hm_store, key);
	if (!node)
		node = NULL;
	return (node);
}

t_bool	env_unset(t_env *env, const char *key)
{
	if (!env_get_node_for_key(env, key))
		return (FALSE);
	hm_remove(env->hm_store, key, env_node_destroy);
	return (TRUE);
}

size_t	env_size(t_env *env)
{
	return (env->store_size);
}

void	env_destroy(t_env *env)
{
	if (env->hm_store)
		hm_destroy(env->hm_store, env_node_destroy);
	free(env);
}

t_pair	*get_next_pair(t_env *env)
{
	t_pair next;

	next = hm_get_seq(env->hm_store);
	return (pair_create(next.f.key, next.s.value));
}

char	**env_to_array(t_env *_env, e_scope scope)
{
	char		**env;
	size_t		count;
	t_pair		*pair;
	t_env_node	*node;

	env = (char **)malloc(sizeof(char*) * g_environ_size);
	if (!env)
		return (NULL);
	count = 0;
	while (count < _env->store_size)
	{
		pair = get_next_pair(_env);
		node = pair->s.value;
		if(node->scope == scope)
		{
			env[count] = node->line;
		}
		pair_destroy(pair);
		count++;
	}
	return (env);
}
