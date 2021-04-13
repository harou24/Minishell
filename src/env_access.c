#include "ft_unistd.h"
#include "env_access.h"
#include <stdlib.h>

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

void	env_set_lasterror(int error)
{
	char	*errstring;

	errstring = ft_itoa(error);
	env_set_s("?", errstring, SCOPE_LOCAL);
	free(errstring);
}
