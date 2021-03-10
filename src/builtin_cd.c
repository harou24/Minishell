#include "bash_ops.h"
#include "env_access"


int	builtin_cd(t_command *cmd)
{
	if (cmd->argv->argc == 1)
		return(directory_change_dir(env_get_home()));
	else
	{
		if (ft_strcmp(cmd->argv->argv[1], ".") == 0)
			return(directory_change_dir(env_get_current_dir()));
		if (ft_strcmp(cmd->argv->argv[1], "..") == 0)
			return(directory_change_dir(env_get_current_dir()));
	}
	return(directory_change_dir(cmd->argv->argv[1]));
}
