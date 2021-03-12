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
		ft_dprintf(cmd->fds[FD_OUT], "unset: not enough arguments");
		return (-1);
	}
	count = 0;
	exit_status = EXIT_SUCCESS;
	while (count < cmd->argv->argc)
	{
		if (!env_unset_s(cmd->argv->argv[count]))
		{
			/*
			man unset says :  	EXIT STATUS

						0    All name operands were successfully unset.

       						>0    At least one name could not be unset.
			*/
			exit_status = EXIT_FAILURE;
		}
		count++;
	}
	exit(exit_status);
}
