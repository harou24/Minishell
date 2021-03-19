#include <assert.h>
#include <stdlib.h>

#include "libft.h"

#include "env_node.h"

t_env_node	*env_node_create(char *line, e_scope scope)
{
	t_env_node	*node;

	assert(line);
	node = ft_calloc(sizeof(t_env_node), 1);
	if (node)
	{
		node->value = ft_strdup(ft_strchr(line, '='));
		node->line = ft_strdup(line);
		node->scope = scope;
	}
	return (node);
}

t_env_node	*env_node_destroy(t_env_node *node)
{
	if (node)
	{
		free(node->value);
		free(node->line);
		free(node);
	}
	return (NULL);
}

void		env_node_destroy_hm(void *_node)
{
	t_env_node *node;

	if (_node)
	{
		node = (t_env_node *)_node;
		free(node->value);
		free(node->line);
		free(node);
	}
}

void		env_node_set_environ_index(t_env_node *node, size_t index)
{
	node->environ_index = index;
}

char        *env_node_get_value(t_env_node *node)
{
	assert(node);
	return (node->value);
}

e_scope     env_node_get_scope(t_env_node *node)
{
	assert(node);
	return (node->scope);
}

/*	
	t_pair      *env_node_pair_from_node(t_env_node *node)

	env_node does not have the key. The key belongs to env.
	I think it is better to keep that way, It would not be 
	clean to have key twice in two different object.
*/

