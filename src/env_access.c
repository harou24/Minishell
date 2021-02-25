#include "env_access.h"

char	*env_get_user(t_env *_env)
{
	return (env_get(_env, "USER"));
}

char	*env_get_host(t_env *_env)
{
	return (env_get(_env, "HOST"));
}

char	*env_get_current_dir(t_env *_env)
{
	return (env_get(_env, "PWD"));
}
