#include "bash_ops.h"
#include <stdlib.h>

int	builtin_exit(t_command *cmd)
{
	unsigned char	exit_status;

	exit_status = EXIT_SUCCESS;
	if (cmd->argv->argc > 2)
	{
		/*error handler*/
		exit(EXIT_FAILURE);
	}
	if (cmd->argv->argc == 2)
		exit_status = (unsigned char)ft_atoi(cmd->argv->argv[1]);
	exit(exit_status);
}
