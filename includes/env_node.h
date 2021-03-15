#ifndef ENV_NODE_H
# define ENV_NODE_H

#include "hashmap.h"

typedef enum	s_scope
{
		DECLARE,
		ENV,
		EXPORT,
		SET
}		e_scope;

typedef struct	s_env_node
{
	char	*value;
	char	*line;
	e_scope	scope;
}		t_env_node;

t_env_node	*env_node_create(const char *line, e_scope scope);
void		env_node_destroy(t_env_node *to_destroy);

#endif
