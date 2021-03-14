#ifndef ENV_NODE_H
# define ENV_NODE_H

#include "pair.h"
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
	t_pair	*key_value_pair;
	char	*line;
	e_scope	scope
}		t_env_node;

t_env_node	*env_node_create(const char *line);
int		build_key_value_pair_from_line(const char *line);
void		env_destroy(t_env_node *to_destroy);

#endif
