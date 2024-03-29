/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:01:01 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:01:02 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <stdlib.h>

#include <sys/wait.h>
#include <unistd.h>

#include "libft.h"
#include "debugger.h"

#include "command.h"
#include "process.h"
#include "executor.h"

#include "bash_ops.h"

#include <string.h>

t_bool	executor_should_run_in_parent(t_execscheme *scheme)
{
	return (scheme->op_type != OP_COMMAND);
}

int	executor_launch_scheme(t_execscheme *scheme)
{
	int	exitstatus;

	exitstatus = execscheme_dispatch(scheme->rel_type[NEXT_R])(scheme);
	if (exitstatus != 0)
	{
		dbg("%s\n", "Failed to execute scheme !");
		return (exitstatus);
	}
	return (0);
}

static int	executor_launch_processes(t_execscheme *scheme)
{
	int		error;

	error = 0;
	while (scheme)
	{
		error = executor_launch_scheme(scheme);
		if (error != 0)
			return (error);
		scheme = scheme->next;
	}
	return (error);
}

static int 	executor_get_exitstatus(t_execscheme *scheme)
{
	int	exitstatus;

	exitstatus = 0;
	while (scheme)
	{
		if (scheme->pid > 0 )
		{
			exitstatus = p_wait(&scheme->pid, W_EXITED);
			if (exitstatus != 0)
				return (exitstatus);
		}
		scheme = scheme->next;
	}
	return (exitstatus);
}

int	execute(t_execscheme *rootscheme)
{
	int	exitstatus;

	if (rootscheme == NULL)
		return (0);
	exitstatus = executor_launch_processes(rootscheme);
	if (exitstatus == 0)
		exitstatus = executor_get_exitstatus(rootscheme);
	executor_kill_all(rootscheme);
	return (exitstatus);
}
