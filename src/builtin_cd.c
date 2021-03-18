#include "bash_ops.h"
#include "env_access.h"
#include "filesystem_traversal.h"
#include "ft_printf.h"
#include "path.h"
#include <stdlib.h>

#define DIR_ERROR 0
#define TOO_MANY_ARGS -1

static int 	__go_to_prev_dir()
{
	return (fs_change_dir(env_get_prev_dir()));
}

static int	__go_to_home()
{
	return (fs_change_dir(env_get_home()));
}

static int	__go_to_path(const char *path)
{
	return (fs_change_dir(path));
}

static t_bool	__update_dir_change(char *new_path)
{
	return (env_set_s("OLDPWD", env_get_s("PWD")) && 
			env_set_s("PWD", new_path));
}

static	t_bool	__is_dash(const char *str)
{
	return (ft_strcmp(str, "-") == 0);
}

static t_bool __is_path_in_cdpath(const char *path)
{
	return (path_contains("CDPATH", path));
}

static t_bool	__is_print_path_needed(const char *path)
{
	return (__is_dash(path) || __is_path_in_cdpath(path));
}

static	void	__print_cur_path()
{
	ft_dprintf(STDOUT, "%s\n", env_get_current_dir());
}

static int	__exec_cd(t_command *cmd)
{
	int error;

	if (cmd->argv->argc == 1)
		error = __go_to_home();
	else if (cmd->argv->argc == 2)
	{
		if (__is_dash(cmd->argv->argv[1]))
			error = __go_to_prev_dir();
		else
			error = __go_to_path(cmd->argv->argv[1]);
	}
	else
		error = TOO_MANY_ARGS;
	return (error);
}

int		builtin_cd(t_command *cmd)
{
	int	error;

	if (cmd->argv->argc > 0 && cmd->argv->argv <= 2)
		error = __exec_cd(cmd);
	else
	{
		/*handle errors*/
		exit(EXIT_FAILURE);
	}
	if (!(error == DIR_ERROR && __update_dir_change(cmd->argv->argv[1])))
		exit(EXIT_FAILURE);
	if (__is_print_path_needed(cmd->argv->argv[1]))
		__print_cur_path();
	exit(EXIT_SUCCESS);


