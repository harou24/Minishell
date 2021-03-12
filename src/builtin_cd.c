#include "bash_ops.h"
#include "env_access.h"
#include "filesystem_traversal.h"
#include "ft_printf.h"
#include "path.h"
#include <stdlib.h>

static int 	__go_to_prev_dir()
{
	return (fs_change_dir(env_get_prev_dir()));
}

static int	__got_to_home()
{
	return (fs_change_dir(env_get_home()));
}

static t_bool	__update_dir_change_in_env(t_command *cmd)
{
	if (!env_set_s("OLDPWD", env_get_s("PWD")))
		return (FALSE);
	return (env_set_s("PWD", cmd->argv->argv[1]));
}

static int	__got_to_path(t_command *cmd)
{
	int ret;

	if (ft_strcmp(cmd->argv->argv[1], "-") || path_contains("CDPATH", cmd->argv->argv[1]))
	{
		ret = __go_to_prev_dir();
		ft_dprintf(cmd->fds[FD_OUT], "%s\n", env_get_current_dir());
	}
	else
		ret = fs_change_dir(cmd->argv->argv[1]);
	if (ret == 0 && __update_dir_change_in_env(cmd))
		return (ret);
	return (ret);
}

int		builtin_cd(t_command *cmd)
{
	int	ret;

	if (cmd->argv->argc == 1)
		ret = __got_to_home();
	else if (cmd->argv->argc == 2)
		ret = __got_to_path(cmd);
	else
	{
		/*handle errors*/
		return (-1);
	}
	if (ret != 0)
		return (-1);
	exit(EXIT_SUCCESS);
}
