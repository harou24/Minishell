#include "bash_ops.h"
#include "env_singleton.h"
#include "ft_printf.h"

int	builtin_unset(t_command *cmd)
{
	int	count;
	int	exit_status;

	if (cmd->argv->argc < 2)
	{
		/*later use error handler ?*/
		ft_dprintf(STDERR, "unset: not enough arguments");
		return (-1);
	}
	count = 1;
	exit_status = EXIT_SUCCESS;
	while (count < cmd->argv->argc)
	{
		if (!env_unset_s(cmd->argv->argv[count]))
			exit_status = EXIT_FAILURE;
		count++;
	}
	exit(exit_status);
}
