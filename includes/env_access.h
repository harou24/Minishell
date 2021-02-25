#ifndef ENV_ACCESS_H
# define ENV_ACCESS_H

#include "env.h"

char	*env_get_user(t_env *_env);
char	*env_get_host(t_env *_env);
char	*env_get_working_dir(t_env *_env);

#endif
