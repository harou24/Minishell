#ifndef ENV_H
# define ENV_H

#include "pair.h"
#include "hashmap.h"

typedef struct	senv
{
	void	*hm_store;
	size_t	store_size;
}		t_env;

t_env	*env_create(const char **env);
char	*env_get(t_env *env, const char *key);
void	*env_set(t_env *env, const char *key, char *value);
void	env_unset(t_env *env, const char *key);
size_t	env_size(t_env *env);
void	env_destroy(t_env *env);
void	*set_env_array(t_env *this_env, const char **env);
int	put_env_line_into_store(t_env *env, const char *env_line, void *hm_store);
t_pair	*split_line_into_key_value_pair(const char *line);
t_pair	*get_next(t_env *env);
void	env_print_out(t_env *env, int fd);
#endif
