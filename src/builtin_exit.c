#include "bash_ops.h"
#include <stdlib.h>

int	builtin_exit(t_command *cmd)
{
	unsigned char	code;

	code = EXIT_SUCCESS;
	if (cmd->argv->argc > 2)
	{
		/*error handler*/
		return (-1);
	}
	if (cmd->argv->argc == 2)
		code = (unsigned char)ft_atoi(cmd->argv->argv[1]);
	exit(code);
}
