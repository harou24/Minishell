#include "env_node.h"
#include "libft.h"
#include <stdlib.h>

t_env_node	*env_node_create(const char *line, e_scope scope)
{
	t_env_node	*node;

	node = ft_calloc(sizeof(t_env_node), 1);
	if (!node)
		return (NULL);
	node->value = ft_strdup(ft_strchr(line, '='));
	node->line = ft_strdup(line);
	if (!node->value || !node->line)
		return (NULL);
	node->scope = scope;
	return (node);
}

void		env_node_destroy(void *to_destroy)
{
	t_env_node *node = (t_env_node *)to_destroy;
	free(node->value);
	free(node->line);
	free(node);
}

char        *env_node_get_value(t_env_node *node)
{
	return (node->value);
}

e_scope     env_node_get_scope(t_env_node *node)
{
	return (node->scope);
}

/*	
	t_pair      *env_node_pair_from_node(t_env_node *node)

	env_node does not have the key. The key belongs to env.
	I think it is better to keep that way, It would not be 
	clean to have key twice in two different object.
*/

