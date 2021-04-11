#include <stdlib.h>

#include "environ.h"
#include "env_singleton.h"
#include "env.h"

extern t_env	*g_env__;

char	**env_to_array_s(e_scope scope)
{
	return (env_to_array(g_env__, scope));
}
