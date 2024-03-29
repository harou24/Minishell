#ifndef ENV_H
# define ENV_H

# include "pair.h"
# include "hashmap.h"
# include "env_node.h"

# define HASHMAP_SIZE 1024

typedef struct s_env
{
	void		*hm_store;
}				t_env;

t_env			*env_create(const char **environ);
t_env			*env_destroy(t_env **env);

char			*env_get(t_env *env, const char *key);
t_bool			env_set(t_env *env, const char *key, char *value,
					t_scope_e scope);
t_bool			env_unset(t_env *env, const char *key);
size_t			env_size(t_env *env);
char			**env_to_array(t_env *env, t_scope_e scope);

//t_pair			*env_pair_create_from_line(const char *line);

/* internal */
t_env_node		*env_get_node_for_key(t_env *env, const char *key);
t_env_node		*env_get_next_node(t_env *env);
void			*env_bootstrap_from_environ(const char **env);

t_bool			env_add_to_environ(t_env_node *node,
					const char *key,
					char *value,
					t_scope_e scope);

t_bool			env_insert_from_line(const char *env_line,
					void *hm_store);

t_env_node		*env_get_node_for_key(t_env *env,
					const char *key);

#endif
