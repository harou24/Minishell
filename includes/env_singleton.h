#ifndef ENV_SINGLETON_H
# define ENV_SINGLETON_H

#include "env.h"

t_env	*env_init();
void	env_deinit();

void	*env_get_s(const char *key);
t_bool	env_set_s(const char *key, void *value);
t_bool	env_unset_s(const char *key);

#endif
