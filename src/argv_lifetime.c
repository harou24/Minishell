/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   argv_lifetime.c                                    :+:    :+:            */
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

t_argv	*argv_create(char *path)
{
	const size_t	vec_size = 16;
	t_argv			*argv;

	assert(path);
	argv = ft_calloc(sizeof(t_argv), 1);
	if (argv)
	{
		if (!vector(&argv->vec, V_CREATE, vec_size, NULL))
		{
			free(argv);
			return (NULL);
		}
		vector(&argv->vec, V_PUSHBACK, 0, NULL);
		argv_push(argv, path);
		assert(argv_get_size(argv) == 1);
	}
	return (argv);
}

t_argv	*argv_destroy(t_argv **argv)
{
	if (!argv)
		return (NULL);
	if (*argv)
	{
		vector(&(*argv)->vec, V_DESTROY, TRUE, NULL);
		free(*argv);
	}
	return ((*argv = NULL));
}
