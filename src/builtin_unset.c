#include "bash_ops.h"
#include "env_singleton.h"
#include "ft_printf.h"

int	builtin_unset(t_command *cmd)
{
	int	index;
	int	exit_status;

	if (cmd->argv->argc < 2)
	{
		ft_dprintf(STDERR, "unset: not enough arguments");
		return (-1);
	}
	index = 1;
	exit_status = EXIT_SUCCESS;
	while (index < cmd->argv->argc)
	{
		if (!env_unset_s(cmd->argv->argv[index]))
			exit_status = EXIT_FAILURE;
		index++;
	}
	return (exit_status);
}
