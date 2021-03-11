#include "bash_ops.h"
#include "env_access.h"
#include "directory.h"
#include "ft_printf.h"
#include <stdlib.h>

int 	go_to_prev_dir()
{
	return (directory_change_dir(env_get_prev_dir()));
}

int	go_to_home()
{
	return (directory_change_dir(env_get_home()));
}

int	go_to_path(const char *path)
{
	return (directory_change_dir(path));
}

int	builtin_cd(t_command *cmd)
{
	if (cmd->argv->argc == 1)
		return(go_to_home());
	else
	{
		if (cmd->argv->argv[1][0] == '.')
			return (go_to_path(cmd->argv->argv[1]));	/*check_for_real_path*/
		else if (ft_strcmp(cmd->argv->argv[1], "-"))
		{
			int ret = go_to_prev_dir();
			ft_dprintf(STDERR, "%s\n", env_get_current_dir());
			return (ret);
		}
		else
			return (go_to_path(cmd->argv->argv[1]));
	}
}
