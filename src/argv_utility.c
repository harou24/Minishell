/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   argv_utility.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 20:56:10 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 20:56:17 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <stdlib.h>

#include "libft.h"
#include "debugger.h"

#include "argv.h"

char	*argv_get(t_argv *argv, int index)
{
	assert(argv);
	return ((char *)vector(&argv->vec, V_PEEKAT, index, NULL));
}

t_bool	argv_push(t_argv *argv, char *arg)
{
	assert(argv);
	assert(argv->vec);
	if (!arg)
		return (FALSE);
	vector(&argv->vec, V_POPBACK, 0, NULL);
	return (vector(&argv->vec, V_PUSHBACK, 0, arg)
		&& vector(&argv->vec, V_PUSHBACK, 0, NULL));
}

const char	**argv_get_array(t_argv *argv)
{
	assert(argv);
	return ((const char **)vector(&argv->vec, V_MEM, 0, NULL));
}

size_t	argv_get_size(t_argv *argv)
{
	assert(argv);
	return (*(size_t *)vector(&argv->vec, V_SIZE, 0, NULL) - 1);
}
