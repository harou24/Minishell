#include "libft.h"
#include "env.h"
#include <stdlib.h>

#define HASHMAP_SIZE 1000

t_pair	*split_line_into_key_value_pair(const char *_line)
{
	t_pair	*pair;
	int	equal_sign_index;
	char	*key;
	char	*value;

	equal_sign_index = ft_strclen(_line, '=');
	key = ft_strsub(_line, 0, equal_sign_index);
	value = ft_strsub(_line, equal_sign_index + 1, ft_strlen(_line) - equal_sign_index);
	pair = pair_create(key, value);
	if (!pair)
	{
		pair_destroy(pair);
		return (NULL);
	}
	return (pair);
}

int	put_env_line_into_store(t_env *_env, const char *_env_line, void *_hm_store)
{
	t_pair	*pair;

	pair = split_line_into_key_value_pair(_env_line);
	if (!pair || !hm_set(_hm_store, pair->f.key, pair->s.value))
	{
		free(pair->f.key);
		env_destroy(_env);
		return (0);
	}
	free(pair->f.key);
	pair_destroy(pair);
	return (1);
}

void	*set_env_array(t_env *_this_env, const char **_env)
{
	void		*hm_store;
	int		count;

	hm_store = hm_new(HASHMAP_SIZE);
	if (!hm_store)
		return (NULL);
	count = 0;
	while(_env[count])
	{
		if (!put_env_line_into_store(_this_env, _env[count], hm_store))
			return (NULL);
		count++;
	}
	return (hm_store);
}


t_env	*env_create(const char **_env)
{
	t_env	*env;

	env = ft_calloc(sizeof(t_env), 1);
	if (!env)
		return (NULL);
	env->store_size = ft_arraylen((const void**)_env);
	env->hm_store = set_env_array(env, _env);
	if (!env->hm_store)
		return (NULL);
	return (env);
}

char	*env_get(t_env *env, const char *_var)
{
	return ((char *)hm_get(env->hm_store, _var));
}

void	*env_set(t_env *_env, char *_var, char *_value)
{
	return (hm_set(_env->hm_store, _var, _value));
}

void	env_unset(t_env *_env, char *_var)
{
	hm_remove(_env->hm_store, _var, free);
}

size_t	env_size(t_env *_env)
{
	return (_env->store_size);
}

void	env_destroy(t_env *_env)
{
	if (_env->hm_store)
		hm_destroy(_env->hm_store, free);
	free(_env);
}
