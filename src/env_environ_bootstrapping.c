/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_environ_bootstrapping.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 20:58:22 by sverschu      #+#    #+#                 */
/*   Updated: 2021/05/06 19:06:39 by haachtch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "debugger.h"
#include "libft.h"
#include "vector.h"
#include "environ.h"

#include "env.h"

void	*env_bootstrap_from_environ(const char **env)
{
	void	*hm_store;
	int		index;

	hm_store = hm_new(HASHMAP_SIZE);
	if (!hm_store)
		return (NULL);
	index = 0;
	while (env[index])
	{
		if (!env_insert_from_line(env[index], hm_store))
		{
			hm_destroy(hm_store, env_node_destroy_hm);
			return (NULL);
		}
		index++;
	}
	return (hm_store);
}

t_bool	env_add_to_environ(t_env_node *node,
							const char *key,
							char *value,
							t_scope_e scope)
{
	char	*line;

	if (scope == SCOPE_ENVIRON || node->scope == SCOPE_ENVIRON)
	{
		dbg("Adding key{%s}, value{%s} to environ!\n", key, value);
		line = ft_strjoin_multi(3, key, "=", value);
		if (node->environ_index >= 0)
		{
			if (!environ_set(node->environ_index, line))
				return (FALSE);
		}
		else
		{
			if (!environ_add(line))
				return (FALSE);
			node->environ_index = environ_size() - 1;
		}
		return (TRUE);
	}
	else
	{
		return (FALSE);
	}
}
