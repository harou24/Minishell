#ifndef ENV_H
# define ENV_H

#include "pair.h"
#include "hashmap.h"
#include "env_node.h"

typedef struct	senv
{
	void	*hm_store;
	size_t	store_size;
}		t_env;

t_env		*env_create(const char **env);
char		*env_get(t_env *env, const char *key);
void		*env_set(t_env *env, const char *key, char *value);
t_bool		env_unset(t_env *env, const char *key);
size_t		env_size(t_env *env);
void		env_destroy(t_env *env);


					/*internal*/

void		*env_bootstrap_from_environ(t_env *this_env, const char **env);
int		env_insert_from_line(t_env *env, const char *env_line, void *hm_store);
t_pair		*pair_create_from_line(const char *line);
t_pair		*get_next_pair(t_env *env);
char		**env_to_array(t_env *_env, e_scope scope);
t_env_node	*env_get_node_for_key(t_env *env, const char *key);

#endif
