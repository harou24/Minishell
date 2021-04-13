#include <stdlib.h>

#include "environ.h"
#include "env_singleton.h"
#include "env.h"

extern t_env	*g_env__;

char	**env_to_array_s(e_scope scope)
{
	return (env_to_array(g_env__, scope));
}

t_bool	env_unset_s(const char *key)
{
	if (g_env__)
		env_unset(g_env__, key);
	return (TRUE);
}
