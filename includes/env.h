#ifndef ENV_H
# define ENV_H

#include "pair.h"
#include "hashmap.h"

typedef struct	s_env {
		void	*hm_store;
		size_t	store_size;
}		t_env;

t_env	*env_create(const char **_env);
char	*env_get(t_env *env, const char *_var);
void	*env_set(t_env *env, char *_var, char *_value);
void	env_unset(t_env *env, char *_var);
size_t	env_size(t_env *env);
void	env_destroy(t_env *env);
void	*set_env_array(t_env *_this_env, const char **_env);
int	put_env_line_into_store(t_env *_env, const char *_env_line, void *_hm_store);
t_pair	*split_line_into_key_value_pair(const char *_line);

#endif
