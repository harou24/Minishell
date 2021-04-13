#ifndef ENV_NODE_H
# define ENV_NODE_H

# include "hashmap.h"
# include "libft.h"
# include "pair.h"

typedef enum e_scope_e
{
	SCOPE_LOCAL,
	SCOPE_ENVIRON
}	t_scope_e;

typedef struct s_env_node
{
	char		*key;
	char		*value;
	char		*line;
	int			environ_index;
	t_scope_e	scope;
}				t_env_node;

t_env_node	*env_node_create(const char *key, const char *value,
				t_scope_e scope);

t_env_node	*env_node_destroy(t_env_node **node);
void		env_node_destroy_hm(void *node);

void		env_node_set_environ_index(t_env_node *node, int index);

t_bool		env_node_update(t_env_node *node, char *key, char *value);
char		*env_node_get_value(t_env_node *node);
t_scope_e	env_node_get_scope(t_env_node *node);

t_pair		*env_node_pair_from_node(t_env_node *node);

#endif
