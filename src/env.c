#include "libft.h"
#include "env.h"

t_env	env_create(void)
{
	t_env	*env;

	env = ft_calloc(sizeof(t_env), 1);
	if (!env)
		return (NULL);
	env->hm_store = get_hm_store();
	if (!env->hm_store)
		return (NULL);
	return (env);
}

/*this should be internal function */
static t_hashmap	*get_hm_store(void)
{
	void		*hm_store;
	extern char	**environ;
	char		**env;
	char		*key;
	char		*value;
	int		equal_sign_index;
	int		count;

	hm_store = hm_new(ft_arraylen((const void **)env));
	if (!hm_store)
		return (NULL);
	env = environ;
	key = NULL;
	value = NULL;
	count = 0;
	equal_sign_index = 0;
	while(env[count])
	{
		equal_sign_index = ft_strclen(env[i], '=');
		key = ft_strsub(env[i], 0, equal_sign_index);
		if (!key)
			return (NULL);
		value = ft_strsub(env[i], equal_sing_index + 1, ft_strlen(env[i]) - equal_sign_index);
		if (!value)
			return (NULL);
		if (!hm_set(hm_store, key, value))
			return (NULL);
		count++;
	}
	return (hm_store);
}

char	*env_get(t_env *env, const char *_var)
{
	return ((char *)hm_get(env->hm_store, _var));
}

void	*env_update(t_env *_env, const char *_var, const char *_new_value)
{
	return (hm_set(env->hm_store, _var, _new_value));
}

void	*env_add(t_env *_env, const char *_var, const char *_value)
{
	return (hm_set(env->hm_store, _var, _value));
}

void	*env_remove(t_env *_env, const char *_var)
{
	/* NEED TO UPDATE LIBHASHMAP TO ADD REMOVE FUNTCION */
	return (NULL);
}

void	env_destroy(t_env *env)
{
	hm_destroy(env->hm_store, free);
}
