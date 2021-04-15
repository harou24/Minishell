/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   argv.c                                             :+:    :+:            */
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
	assert (*(size_t *)vector(&argv->vec, V_SIZE, 0, NULL) >= 1);
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
	assert (*(size_t *)vector(&argv->vec, V_SIZE, 0, NULL) >= 1);
	return (*(size_t *)vector(&argv->vec, V_SIZE, 0, NULL) - 1);
}

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
		assert (*(size_t *)vector(&argv->vec, V_SIZE, 0, NULL) == 2);
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

void	argv_pretty_dump(t_argv *argv, int indent)
{
	size_t	i;

	assert(argv);
	if (argv_get_size(argv) == 0)
		return ;
	dbg("%*s: %i\n", indent, "Argc ", argv_get_size(argv));
	dbg("%*s: \n", indent, "Argv ");
	i = 0;
	while (i < argv_get_size(argv))
	{
		dbg("%*s[%i] : %s\n", (int)(indent) - 2, "", i, argv_get(argv, i));
		i++;
	}
}
