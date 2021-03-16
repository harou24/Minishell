#ifndef ENV_NODE_H
# define ENV_NODE_H

#include "hashmap.h"
#include "libft.h"

typedef enum	s_scope
{
		/*
			env,export,set without arguments print out for each one of them different "scope".
			DECLARE,
			ENV,
			EXPORT,
			SET
		*/
		LOCAL,
		ENVIRON
}		e_scope;

typedef struct	s_env_node
{
	char	*value;
	char	*line;
	size_t	environ_index; // NOT USED
	e_scope	scope;
}		t_env_node;

t_env_node	*env_node_create(const char *line, e_scope scope);
void		env_node_destroy(void *to_destroy);

t_bool		env_node_update(t_env_node *node, char *key, char *value);
char		*env_node_get_value(t_env_node *node);
e_scope		env_node_get_scope(t_env_node *node);

#endif
