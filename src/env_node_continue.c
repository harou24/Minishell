#include "env_node.h"

char	*env_node_get_value(t_env_node *node)
{
	return (node->value);
}

e_scope	env_node_get_scope(t_env_node *node)
{
	return (node->scope);
}

t_pair	*env_node_pair_from_node(t_env_node *node)
{
	return (pair_create(node->key, node->value));
}
