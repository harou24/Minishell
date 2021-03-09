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
