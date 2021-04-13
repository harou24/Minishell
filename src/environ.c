/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environ.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 20:59:27 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 20:59:29 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "debugger.h"
#include "libft.h"
#include "vector.h"

#include "environ.h"

void	*g_environ_vec__ = NULL;

t_bool	environ_init(char **environ)
{
	return (g_environ_vec__ != NULL
		|| vector(&g_environ_vec__, V_ADOPT,
			ft_array_len((const void **)environ) + 1, environ));
}

t_bool	environ_deinit(void)
{
	return (!g_environ_vec__
		|| vector(&g_environ_vec__, V_DESTROY, TRUE, NULL) == NULL);
}
