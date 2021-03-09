#include "bash_ops.h"

int	builtin_cd(t_command *cmd)
{
	if (cmd->argv->argc == 1)
		return(directory_change_dir());
}
