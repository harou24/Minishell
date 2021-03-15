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

void		env_node_destroy(t_env_node *to_destroy)
{
	free(to_destroy->value);
	free(to_destroy->line);
	free(to_destroy);
}
