/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 20:57:32 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 20:57:34 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <stdlib.h>

#include "ft_printf.h"
#include "debugger.h"
#include "environ.h"
#include "env_singleton.h"
#include "bash_ops.h"

static char	**environ_sorted(char **environ)
{
	char	**sorted_environ;

	sorted_environ = ft_calloc(sizeof(char *),
			ft_array_len((const void **)environ) + 1);
	if (sorted_environ)
	{
		ft_memcpy(sorted_environ, environ,
			sizeof(char *) * ft_array_len((const void **)environ));
		bubblesort_lexical(sorted_environ);
	}
	return (sorted_environ);
}

static int	__dump_environ(void)
{
	char	**environ;
	size_t	i;

	environ = environ_sorted(environ_get());
	if (!environ)
	{
		dbg("Failed to get environ for dumping!\n", "");
		return (-1);
	}
	i = 0;
	while (environ[i] != NULL)
	{
		ft_printf("%s\n", environ[i]);
		i++;
	}
	free(environ);
	return (0);
}

static int	__export_to_environ(const char **argv, size_t argc)
{
	size_t	i;

	i = 1;
	while (i < argc)
	{
		if (!env_set_s_line(argv[i], SCOPE_ENVIRON))
		{
			dbg("Failed export var: %s to environ!\n", argv[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	builtin_export(t_command *cmd)
{
	const size_t	argc = argv_get_size(cmd->argv);
	const char		**argv = argv_get_array(cmd->argv);

	if (argc == 1)
		return (__dump_environ());
	else
		return (__export_to_environ(argv, argc));
}
