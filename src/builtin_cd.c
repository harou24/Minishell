#include "bash_ops.h"
#include "env_access.h"
#include "filesystem_traversal.h"
#include "ft_printf.h"
#include "path.h"
#include <stdlib.h>

#define DIR_HAS_CHANGED 0

static int 	__go_to_prev_dir()
{
	return (fs_change_dir(env_get_prev_dir()));
}

static int	__go_to_home()
{
	return (fs_change_dir(env_get_home()));
}

static t_bool	__update_dir_change(t_command *cmd)
{
	return (env_set_s("OLDPWD", env_get_s("PWD")) && 
			env_set_s("PWD", cmd->argv->argv[1]));
}

static int	__go_to_path(t_command *cmd)
{
	int dir_change;

	if (ft_strcmp(cmd->argv->argv[1], "-") || path_contains("CDPATH", cmd->argv->argv[1]))
	{
		dir_change = __go_to_prev_dir();
		ft_dprintf(cmd->fds[FD_OUT], "%s\n", env_get_current_dir());
	}
	else
		dir_change = fs_change_dir(cmd->argv->argv[1]);
	if (dir_change == DIR_HAS_CHANGED)
		__update_dir_change(cmd);
	return (dir_change);
}

int		builtin_cd(t_command *cmd)
{
	int	dir_change;

	if (cmd->argv->argc == 1)
		dir_change = __go_to_home();
	else if (cmd->argv->argc == 2)
		dir_change = __go_to_path(cmd);
	else
	{
		/*handle errors*/
		return (-1);
	}
	if (dir_change != DIR_HAS_CHANGED)
		return (-1);
	exit(EXIT_SUCCESS);
}
