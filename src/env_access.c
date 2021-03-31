#include "ft_unistd.h"
#include "env_access.h"

char	*env_get_user(void)
{
	return (env_get_s("USER"));
}

char	*env_get_host(void)
{
	return (ft_gethostname());
}

char	*env_get_current_dir(void)
{
	return (env_get_s("PWD"));
}

char	*env_get_prev_dir(void)
{
	return (env_get_s("OLDPWD"));
}

char	*env_get_home(void)
{
	return (env_get_s("HOME"));
}

char	*env_get_path(void)
{
	return (env_get_s("PATH"));
}

char	*env_get_cdpath(void)
{
	return (env_get_s("CDPATH"));
}
