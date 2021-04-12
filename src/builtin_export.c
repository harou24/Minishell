#include <assert.h>
#include <stdlib.h>

#include "ft_printf.h"
#include "debugger.h"
#include "environ.h"
#include "env_singleton.h"
#include "bash_ops.h"

static char	**environ_sorted(char **environ)
{
	char **sorted_environ;

	sorted_environ = ft_calloc(sizeof(char *), ft_array_len((const void **)environ) + 1);
	if (sorted_environ)
	{
		ft_memcpy(sorted_environ, environ, sizeof(char *) * ft_array_len((const void **)environ));
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

static int	__export_to_environ(t_command *cmd)
{
	int	i;

	i = 1;
	while (i < cmd->argv->argc)
	{
		if (!env_set_s_line(cmd->argv->argv[i], SCOPE_ENVIRON))
			return (1);
		i++;
	}
	return (0);
}

int	builtin_export(t_command *cmd)
{
	if (cmd->argv->argc == 1)
		return (__dump_environ());
	else
		return (__export_to_environ(cmd));
}
