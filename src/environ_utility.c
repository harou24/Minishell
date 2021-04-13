/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environ_utility.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 20:59:33 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 20:59:34 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "vector.h"

#include "environ.h"

extern void	*g_environ_vec__;

size_t	environ_size(void)
{
	return (*(size_t *)vector(&g_environ_vec__, V_SIZE, 0, NULL) - 1);
}

void	environ_remove(size_t index)
{
	free(vector(&g_environ_vec__, V_POPAT, index, NULL));
}

char	**environ_get(void)
{
	if (g_environ_vec__)
		return ((char **)vector(&g_environ_vec__, V_MEM, 0, NULL));
	return (NULL);
}

t_bool	environ_set(size_t index, char *line)
{
	return (vector(&g_environ_vec__, V_REPLACE, index, line) != NULL);
}

t_bool	environ_add(char *line)
{
	vector(&g_environ_vec__, V_REPLACE, environ_size(), line);
	vector(&g_environ_vec__, V_PUSHBACK, 0, NULL);
	return (TRUE);
}
