#include "bash_ops.h"
#include <stdlib.h>

int	builtin_exit(t_command *cmd)
{
	unsigned char	exit_code;

	exit_code = EXIT_SUCCESS;
	if (cmd->argv->argc > 2)
	{
		/*error handler*/
		return (-1);
	}
	if (cmd->argv->argc == 2)
		exit_code = (unsigned char)ft_atoi(cmd->argv->argv[1]);
	exit(exit_code);
}
