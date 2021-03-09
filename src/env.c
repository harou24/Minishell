#include "libft.h"
#include "env.h"
#include <stdlib.h>

#define HASHMAP_SIZE 1000

t_pair	*split_line_into_key_value_pair(const char *line)
{
	t_pair	*pair;
	int	equal_sign_index;
	char	*key;
	char	*value;

	equal_sign_index = ft_strclen(line, '=');
	key = ft_strsub(line, 0, equal_sign_index);
	value = ft_strsub(line, equal_sign_index + 1, ft_strlen(line) - equal_sign_index);
	pair = pair_create(key, value);
	if (!pair)
	{
		pair_destroy(pair);
		return (NULL);
	}
	return (pair);
}

int	put_env_line_into_store(t_env *env, const char *envline, void *hm_store)
{
	t_pair	*pair;

	pair = split_line_into_key_value_pair(envline);
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

void	*set_env_array(t_env *this_env, const char **env)
{
	void		*hm_store;
	int		count;

	hm_store = hm_new(HASHMAP_SIZE);
	if (!hm_store)
		return (NULL);
	count = 0;
	while(env[count])
	{
		if (!put_env_line_into_store(this_env, env[count], hm_store))
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
	this_env->hm_store = set_env_array(this_env, env);
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

void	env_unset(t_env *env, const char *key)
{
	hm_remove(env->hm_store, key, free);
}

size_t	env_size(t_env *env)
{
	return (env->store_size);
}

void	env_destroy(t_env *env)
{
	if (env->hm_store)
		hm_destroy(env->hm_store, free);
	free(env);
}
