/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_execbin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 20:59:39 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 20:59:40 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "libft.h"
#include "libprintf.h"
#include "debugger.h"

#include "filesystem.h"
#include "environ.h"
#include "env_access.h"
#include "bash_ops.h"
#include "path.h"

char	*get_relative_path(char *fname)
{
	return (ft_strjoin_multi(2, env_get_current_dir(), fname));
}

t_bool	is_absolute_path(char *fname)
{
	return (ft_strncmp(fname, "./", 2) == 0
		|| ft_strncmp(fname, "../", 2) == 0
		|| ft_strncmp(fname, "/", 1) == 0);
}

t_bool	is_relative_path(char *fname)
{
	char	*abspath;

	abspath = get_relative_path(fname);
	if (file_is_executable(abspath))
	{
		free (abspath);
		return (TRUE);
	}
	free (abspath);
	return (FALSE);
}

int	op_execbin(t_command *cmd)
{
	char		*abspath;

	if (is_absolute_path(cmd->path))
		abspath = cmd->path;
	else if (is_relative_path(cmd->path))
		abspath = get_relative_path(cmd->path);
	else
		abspath = path_expand(env_get_path(), cmd->path);
	if (abspath && file_exists(abspath))
	{
		if (!file_is_executable(abspath))
		{
			ft_dprintf(STDERR, "%s: %s\n", "minishell: permission denied ",
				cmd->path);
			exit(128);
		}
		argv_transform_escape_chars(cmd->argv);
		execve(abspath, (char *const *)argv_get_array(cmd->argv),
			environ_get());
		dbg("execve failed for %s with error : %s\n", abspath, strerror(errno));
		exit (1);
	}
	ft_dprintf(STDERR, "%s: %s\n", "minishell: command not found", cmd->path);
	exit(127);
}
