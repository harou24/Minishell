#include <assert.h>
#include <stdlib.h>

#include "libft.h"
#include "ft_printf.h"

#include "env_singleton.h"
#include "bash_ops.h"

int			op_assignment(t_command *cmd)
{
	if (cmd->argv->argc == 3)
	{
		if (env_set_s(cmd->argv->argv[0], cmd->argv->argv[2], SCOPE_LOCAL) == TRUE)
			return (0);
	}
	else if (cmd->argv->argc == 2)
	{
		if (env_unset_s(cmd->argv->argv[0]) == TRUE)
			return (0);
	}
	return (1);
}
