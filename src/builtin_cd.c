#include <assert.h>
#include <stdlib.h>
#include <limits.h>

#include <errno.h>
#include <string.h>

#include "libft.h"

#include "bash_ops.h"
#include "env_access.h"
#include "filesystem_traversal.h"
#include "filesystem.h"
#include "ft_printf.h"
#include "path.h"

static int	update_dir_change(char *new_path)
{
	char	*new_path_tmp;

	new_path_tmp = ft_strdup(new_path);
	env_set_s("OLDPWD", env_get_current_dir(), SCOPE_ENVIRON);
	env_set_s("PWD", new_path_tmp, SCOPE_ENVIRON);
	free(new_path_tmp);
	return (0);
}

static int	cd(char *fname)
{
	if (fs_change_dir(fname) == 0 && update_dir_change(fname) == 0)
		return (0);
	return (1);
}

static int	__exec_cd(char *fname)
{
	char	*new_path;

	if (ft_strcmp(fname, "/") != 0
		&& ft_strcmp(fname, ".") != 0
		&& path_contains(env_get_cdpath(), fname))
	{
		new_path = path_expand(env_get_cdpath(), fname);
		ft_dprintf(STDOUT, "%s\n", new_path);
	}
	else
		new_path = ft_realpath(fname);
	if (cd(new_path) != 0)
	{
		if (!directory_exists(new_path))
			ft_dprintf(STDERR, "cd: not a directory: %s\n", fname);
		else if (!directory_is_openable(new_path))
			ft_dprintf(STDERR, "cd: no such file or directory: %s\n",
				fname);
		free(new_path);
		return (1);
	}
	free(new_path);
	return (0);
}

static int	__handle_cd_tilde(char *fname)
{
	char	*path;

	if (!fname || ft_strncmp("~", fname, 2) == 0
		|| ft_strncmp("~/", fname, 3) == 0)
		return (cd(env_get_home()));
	path = ft_strjoin_multi(3, env_get_home(), "/", fname + 2);
	if (!path)
		return (1);
	if (cd(path) == 0)
	{
		free(path);
		return (0);
	}
	free(path);
	return (1);
}

int	builtin_cd(t_command *cmd)
{
	if (cmd->argv->argc == 1 || ft_strncmp("~", cmd->argv->argv[1], 1) == 0)
		return (__handle_cd_tilde(cmd->argv->argv[1]));
	else if (cmd->argv->argc == 2)
	{
		if (ft_strncmp("-", cmd->argv->argv[1], 2) == 0)
		{
			ft_dprintf(STDOUT, "%s\n", env_get_prev_dir());
			return (cd(env_get_prev_dir()));
		}
		else
			return (__exec_cd(cmd->argv->argv[1]));
	}
	return (1);
}
