#include <assert.h>
#include <stdlib.h>

#include "ft_printf.h"
#include "environ.h"
#include "env_singleton.h"
#include "bash_ops.h"

static int	__dump_environ(void)
{
	char	**environ;

	environ = environ_get();
	assert(environ);
	while (*environ != NULL)
	{
		ft_printf("%s\n", *environ);
		environ++;
	}
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
