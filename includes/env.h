#ifndef ENV_H
# define ENV_H

#include "hashmap.h"

typedef struct	s_env {
		void	*hm_store;
		size_t	store_size;
}		t_env;

t_env	*env_create(const char **_env);
char	*env_get(t_env *env, const char *_var);
void	*env_set(t_env *env, char *_var, char *_value);
void	*env_remove(t_env *env, const char *_var);
size_t	env_size(t_env *env);
void	env_destroy(t_env *env);

#endif
