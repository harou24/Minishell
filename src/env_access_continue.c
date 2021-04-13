#include "env_access.h"

char	*env_get_user(void)
{
	return (env_get_s("USER"));
}

char	*env_get_path(void)
{
	return (env_get_s("PATH"));
}

char	*env_get_cdpath(void)
{
	return (env_get_s("CDPATH"));
}
