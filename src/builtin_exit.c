#include "bash_ops.h"
#include <stdlib.h>

int	builtin_exit(t_command *cmd)
{
	(void)cmd;
	exit(EXIT_SUCCESS);
	return (0);
}
