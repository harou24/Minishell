#include <assert.h>
#include <stdlib.h>

#include "ft_printf.h"
#include "libft.h"

#include "argv.h"

char	*argv_get(t_argv *argv, int index)
{
	assert(argv);
	assert(index < argv->size); /* assert for testing */

	if (index < argv->size)
		return (argv->argv[index]);
	return (NULL);
}

t_bool	argv_push(t_argv *argv, char *arg)
{
	assert(argv);
	assert(argv->argc < argv->size);

	argv->argv[argv->argc] = arg;
	argv->argc++;
	return (TRUE); /* right now asserting will do, granular control flow not neccessary */
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

#include <stdio.h>

void	argv_pretty_dump(t_argv *argv, int indent)
{
	int	i;

	assert(argv);
	if (argv->argc == 0)
		return ;
	ft_printf("%*s : %i\n", indent, "Argc", argv->argc);
	ft_printf("%*s :\n", indent, "Argv");
	i = 0;
	while (i < argv->argc)
	{
		ft_printf("%*s[%i] : %s\n", (int)(indent * 1.1), "", i, argv->argv[i]);
		i++;
	}
}
