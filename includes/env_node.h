#ifndef ENV_NODE_H
# define ENV_NODE_H

#include "hashmap.h"
#include "libft.h"
#include "pair.h"

typedef enum	s_scope
{
				SCOPE_LOCAL,
				SCOPE_ENVIRON
}				e_scope;

typedef struct	s_env_node
{
	char		*key;
	char		*value;
	char		*line;
	size_t		environ_index;
	e_scope		scope;
}				t_env_node;

t_env_node	*env_node_create(const char *key, const char *value, e_scope scope);
/* needs create function that takes key, value and scope, as you would expect*/

t_env_node	*env_node_destroy(t_env_node **node);
void		env_node_destroy_hm(void *node);

void		env_node_set_environ_index(t_env_node *node, size_t index);

t_bool		env_node_update(t_env_node *node, char *key, char *value);
char		*env_node_get_value(t_env_node *node);
e_scope		env_node_get_scope(t_env_node *node);

t_pair		*env_node_pair_from_node(t_env_node *node);

#endif