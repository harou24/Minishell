#include <stdlib.h>

#include "libft.h"
#include "env_node.h"

t_env_node	*env_node_create_from_pair(t_pair *pair, t_scope_e scope)
{
	t_env_node	*node;

	node = ft_calloc(sizeof(t_env_node), 1);
	if (node)
	{
		node->environ_index = -1;
		node->key = pair->f.key;
		node->value = pair->s.value;
		node->scope = scope;
	}
	return (node);
}

t_env_node	*env_node_create(const char *key,
							const char *value,
							t_scope_e scope)
{
	t_env_node	*node;

	node = ft_calloc(sizeof(t_env_node), 1);
	if (node)
	{
		node->environ_index = -1;
		node->key = ft_strdup(key);
		node->value = ft_strdup(value);
		node->scope = scope;
	}
	if (!node->key || !node->value)
		return (NULL);
	return (node);
}

t_env_node	*env_node_destroy(t_env_node **node)
{
	if (node)
	{
		free((*node)->key);
		free((*node)->value);
		free((*node));
		*node = NULL;
	}
	return (NULL);
}

void	env_node_destroy_hm(void *_node)
{
	t_env_node	*node;

	if (_node)
	{
		node = (t_env_node *)_node;
		free(node->key);
		free(node->value);
		free(node);
	}
}
