#include "env_access.h"

char	*env_get_user()
{
	return (env_get_s("USER"));
}

char	*env_get_host()
{
	return (env_get_s("HOST"));
}

char	*env_get_current_dir()
{
	return (env_get_s("PWD"));
}

char	*env_get_prev_dir()
{
	return (env_get_s("OLDPWD"));
}

char	*env_get_home()
{
	return (env_get_s("HOME"));
}
