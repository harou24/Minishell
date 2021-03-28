#include <assert.h>
#include <stdlib.h>

#include "environ.h"
#include "env_singleton.h"
#include "bash_ops.h"

static int	__dump_environ()
{
	char **environ;

	environ = environ_get();
	assert(environ);
	while (*environ != NULL)
	{
		printf("%s\n", *environ);
		environ++;
	}
	return (0);
}

static int	__export_to_environ(t_command *cmd)
{
	int	i;

	i = 1;
	while (i + 3 <= cmd->argv->argc)
	{
		env_set_s(cmd->argv->argv[i], cmd->argv->argv[i + 2], SCOPE_ENVIRON);
		i += 3;
	}
	return (0);
}

int		builtin_export(t_command *cmd)
{
	if (cmd->argv->argc == 1)
		return (__dump_environ());
	else
		return (__export_to_environ(cmd));
}
