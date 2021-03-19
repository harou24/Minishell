#include <stdlib.h>
#include <assert.h>

#include "libft.h"

#include "env.h"

#define HASHMAP_SIZE 1000

t_pair	*pair_create_from_line(char *line)
{
	t_pair		*pair;
	int			equal_sign_index;
	char		*key;
	t_env_node	*node;

	equal_sign_index = ft_strclen(line, '=');
	key = ft_strsub(line, 0, equal_sign_index);
	assert(key);
	node = env_node_create(line, SCOPE_ENVIRON);
	assert(node);
	pair = pair_create(key, node);
	if (!pair)
	{
		env_node_destroy(node);
		return (NULL);
	}
	return (pair);
}

t_bool	env_insert_from_line(t_env *env, char *envline, void *hm_store)
{
	t_pair	*pair;

	pair = pair_create_from_line(envline);
	if (!pair || !hm_set(hm_store, pair->f.key, pair->s.value))
	{
		free(pair->f.key);
		env_destroy(env);
		return (FALSE);
	}
	free(pair->f.key);
	pair_destroy(pair);
	return (TRUE);
}

void	*env_bootstrap_from_environ(t_env *this_env, char **env)
{
	void		*hm_store;
	int		count;

	hm_store = hm_new(HASHMAP_SIZE);
	if (!hm_store)
		return (NULL);
	count = 0;
	while(env[count])
	{
		if (!env_insert_from_line(this_env, env[count], hm_store))
		{
			hm_destroy(hm_store, env_node_destroy_hm);
			return (NULL);
		}
		count++;
	}
	return (hm_store);
}

t_env	*env_create(const char **environ)
{
	t_env	*this_env;

	this_env = ft_calloc(sizeof(t_env), 1);
	if (this_env)
	{
		this_env->hm_store = env_bootstrap_from_environ(this_env, (char **)environ);
		if (!this_env->hm_store)
		{
			free(this_env);
			return (NULL);
		}
	}
	return (this_env);
}

char	*env_get(t_env *env, const char *key)
{
	t_env_node	*node;

	assert(env);
	assert(key);
	node = env_get_node_for_key(env, key);
	if (node)
		return (node->value);
	else
		return (NULL);
}

void	*env_set(t_env *env, const char *key, char *value)
{
	assert(env);
	assert(key);
	assert(value);
	return (hm_set(env->hm_store, key, value));
}

t_env_node	*env_get_node_for_key(t_env *env, const char *key)
{
	assert(env);
	assert(key);
	return ((t_env_node *)hm_get(env->hm_store, key));
}

t_bool	env_unset(t_env *env, const char *key)
{
	if (!env_get_node_for_key(env, key))
		return (FALSE);
	hm_remove(env->hm_store, key, env_node_destroy_hm);
	return (TRUE);
}

size_t	env_size(t_env *env)
{
	return (hm_size(env->hm_store));
}

void	env_destroy(t_env *env)
{
	if (env->hm_store)
		hm_destroy(env->hm_store, env_node_destroy_hm);
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

	hm_get_seq(NULL); /* resets internal static ptr */
	env = (char **)malloc(sizeof(char*) * (env_size(_env) + 1));
	if (!env)
		return (NULL);
	count = 0;
	while (count < env_size(_env))
	{
		pair = get_next_pair(_env);
		assert(pair);
		node = pair->s.value;
		assert(node);
		if(node->scope == scope)
		{
			env[count] = node->line;
		}
		pair_destroy(pair);
		count++;
	}
	env[count] = NULL;
	return (env);
}
