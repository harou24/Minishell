#ifndef ENV_H
# define ENV_H

#include "hahsmap.h"

typedef struct	s_env {
		void	*hm_store;		
}		t_env;

t_env	env_create(void);
char	*env_get(t_env *env, char *_var);
void	env_update(t_env *_env, const char *_var, const char *_new_value);
void	*env_add(t_env *env, const char *_var, const char *_value);
void	*env_remove(t_env *env, const char *_var);
void	env_destroy(t_env *env);

#endif
