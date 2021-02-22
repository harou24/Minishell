#include "libft.h"
#include "env.h"
#include <stdlib.h>

static void	*load_env(t_env *_this_env, const char **_env)
{
	void		*hm_store;
	t_kv_pair	pair;
	int		equal_sign_index;
	int		count;

	hm_store = hm_new(_this_env->store_size);
	if (!hm_store)
		return (NULL);
	count = 0;
	equal_sign_index = 0;
	while(_env[count])
	{
		equal_sign_index = ft_strclen(_env[count], '=');
		pair.key = ft_strsub(_env[count], 0, equal_sign_index);
		pair.value = ft_strsub(_env[count], equal_sign_index + 1, ft_strlen(_env[count]) - equal_sign_index);
		if (!pair.key || !pair.value || !hm_set(hm_store, pair.key, pair.value))
		{
			free(pair.key);
			free(pair.value);
			env_destroy(_this_env);
			return (NULL);
		}
		free(pair.key);
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
	env->hm_store = load_env(env, _env);
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

void	*env_remove(t_env *_env, const char *_var)
{
	/* NEED TO UPDATE LIBHASHMAP TO ADD REMOVE FUNTCION */
	(void)_env;
	(void)_var;
	return (NULL);
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
