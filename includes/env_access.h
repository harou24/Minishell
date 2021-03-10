#ifndef ENV_ACCESS_H
# define ENV_ACCESS_H

#include "env_singleton.h"

char	*env_get_user();
char	*env_get_host();
char	*env_get_current_dir();
char	*env_get_prev_dir();
char	*env_get_home();

#endif
