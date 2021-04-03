#include <assert.h>
#include <stdlib.h>

#include "libft.h"
#include "debugger.h"

#include "argv.h"

char	*argv_get(t_argv *argv, int index)
{
	if (index < argv->size)
		return (argv->argv[index]);
	return (NULL);
}

t_bool	argv_push(t_argv *argv, char *arg)
{
	argv->argv[argv->argc] = arg;
	argv->argc++;
	return (TRUE);
}

t_argv	*argv_create(int size)
{
	t_argv	*argv;

	if (size == 0)
		return (NULL);
	argv = ft_calloc(sizeof(t_argv), 1);
	if (argv)
	{
		argv->size = size;
		argv->argv = ft_calloc(sizeof(char *), size);
	}
	return (argv);
}

t_argv	*argv_destroy(t_argv **argv)
{
	if (!argv)
		return (NULL);
	if (*argv)
	{
		ft_array_destroy((void **)(*argv)->argv, (*argv)->size);
		free(*argv);
	}
	return ((*argv = NULL));
}

void	argv_pretty_dump(t_argv *argv, int indent)
{
	int	i;

	if (argv->argc == 0)
		return ;
	dbg("%*s : %i\n", indent, "Argc", argv->argc);
	dbg("%*s :\n", indent, "Argv");
	i = 0;
	while (i < argv->argc)
	{
		dbg("%*s[%i] : %s\n", (int)(indent * 1.1), "", i, argv->argv[i]);
		i++;
	}
}
