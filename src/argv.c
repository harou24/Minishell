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
	return ((char *)vector(&argv->argv_vec, V_PEEKAT, index, NULL));
}

t_bool	argv_push(t_argv *argv, char *arg)
{
	return (vector(&argv->argv_vec, V_POPBACK, 0, NULL)
		&& vector(&argv->argv_vec, V_PUSHBACK, 0, arg)
		&& vector(&argv->argv_vec, V_PUSHBACK, 0, NULL));
}

const char	**argv_get_array(t_argv *argv)
{
	return ((const char **)vector(&argv->argv_vec, V_MEM, 0, NULL));
}

size_t	argv_get_size(t_argv *argv)
{
	return (*(size_t *)vector(&argv->argv_vec, V_SIZE, 0, NULL) - 1);
}

t_argv	*argv_create(void)
{
	const size_t	vec_size = 16;
	t_argv			*argv;

	argv = ft_calloc(sizeof(t_argv), 1);
	if (argv)
	{
		argv->argv_vec = vector(&argv->argv_vec, V_CREATE, vec_size, NULL);
		if (!argv->argv_vec)
		{
			free(argv);
			return (NULL);
		}
		vector(&argv->argv_vec, V_PUSHBACK, 0, NULL);
	}
	return (argv);
}

t_argv	*argv_destroy(t_argv **argv)
{
	if (!argv)
		return (NULL);
	if (*argv)
	{
		vector(&(*argv)->argv_vec, V_DESTROY, TRUE, NULL);
		free(*argv);
	}
	return ((*argv = NULL));
}

void	argv_pretty_dump(t_argv *argv, int indent)
{
	size_t	i;

	if (argv_get_size(argv) == 0)
		return ;
	dbg("%*s : %i\n", indent, "Argc", argv_get_size(argv));
	dbg("%*s :\n", indent, "Argv");
	i = 0;
	while (i < argv_get_size(argv))
	{
		dbg("%*s[%i] : %s\n", (int)(indent * 1.1), "", i, argv_get(argv, i));
		i++;
	}
}
