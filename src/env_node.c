#include <assert.h>
#include <stdlib.h>

#include "libft.h"

#include "env_node.h"

t_env_node	*env_node_create_from_pair(t_pair *pair, e_scope scope)
{
	t_env_node	*node;

	assert(pair);
	assert(pair->f.key);
	assert(pair->s.value);
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
t_env_node	*env_node_create(const char *key, const char *value, e_scope scope)
{
	t_env_node	*node;

	assert(key);
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

void		env_node_destroy_hm(void *_node)
{
	t_env_node *node;

	if (_node)
	{
		node = (t_env_node *)_node;
		free(node->key);
		free(node->value);
		free(node);
	}
}

void		env_node_set_environ_index(t_env_node *node, int index)
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

t_pair      *env_node_pair_from_node(t_env_node *node)
{
	assert(node);
	return (pair_create(node->key, node->value));
}

