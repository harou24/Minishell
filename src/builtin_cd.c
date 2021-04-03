#include "bash_ops.h"
#include "env_access.h"
#include "filesystem_traversal.h"
#include "filesystem.h"
#include "ft_printf.h"
#include "path.h"
#include <stdlib.h>
#include <limits.h>

#include <errno.h>
#include <string.h>

#define NO_ERROR_OCCURED 0
#define TOO_MANY_ARGS -1

static int	__exec_cd_home(void)
{
	int	error;
	int	exit_status;
	char	*new_path;

	error = __go_to_home();
	exit_status = EXIT_FAILURE;
	new_path = NULL;
	if (error == NO_ERROR_OCCURED)
		new_path = ft_strdup(env_get_home());
	if (new_path && __update_dir_change(new_path))
		exit_status = EXIT_SUCCESS;
	return (exit_status);
}

static int	__exec_cd_dash(void)
{
	int	error;
	int	exit_status;
	char	*new_path;

	error = __go_to_prev_dir();
	exit_status = EXIT_FAILURE;
	new_path = NULL;
	if (error == NO_ERROR_OCCURED)
		new_path = ft_strdup(env_get_prev_dir());
	if (new_path && __update_dir_change(new_path))
		exit_status = EXIT_SUCCESS;
	return (exit_status);
}

static int	__exec_cd(t_command *cmd)
{
	int	error;
	int	exit_status;
	char	*new_path;

	exit_status = EXIT_FAILURE;
	if (__is_path_in_cdpath(cmd->argv->argv[1]))
		new_path = path_expand(env_get_s("CDPATH"), cmd->argv->argv[1]);
	else
		new_path = ft_realpath(cmd->argv->argv[1]);
	error = __go_to_path(new_path);
	if (new_path && error == NO_ERROR_OCCURED && __update_dir_change(new_path))
		exit_status = EXIT_SUCCESS;
	else if (!fs_has_type(new_path, F_DIR))
		ft_dprintf(STDOUT, "cd: not a directory: %s\n", cmd->argv->argv[1]);
	else
		ft_dprintf(STDOUT, "cd: no such file or directory: %s\n",
			cmd->argv->argv[1]);
	free(new_path);
	return (exit_status);
}

int	builtin_cd(t_command *cmd)
{
	int	exit_status;

	exit_status = EXIT_FAILURE;
	if (cmd->argv->argc > 0 && cmd->argv->argc <= 2)
	{
		if (cmd->argv->argc == 1)
			exit_status = __exec_cd_home();
		else
		{
			if (__is_tilde(cmd->argv->argv[1]))
				exit_status = __exec_cd_home();
			else if (__is_dash(cmd->argv->argv[1]))
				exit_status = __exec_cd_dash();
			else
				exit_status = __exec_cd(cmd);
			if (__is_print_path_needed(cmd->argv->argv[1]))
				__print_cur_path();
		}
	}
	return (exit_status);
}
