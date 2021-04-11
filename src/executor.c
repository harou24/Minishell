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

#include <stdio.h>
#include <string.h>

t_bool	executor_should_run_in_parent(t_execscheme *scheme)
{
	return ((scheme->op_type != OP_COMMAND && scheme->op_type != OP_PATH)
			|| scheme->op_type == OP_ASSIGNMENT);
}

int	executor_launch_scheme(t_execscheme *scheme)
{
	//if (executor_is_builtin(scheme) || executor_is_assignment(scheme))
	//{
	//	return (executor_launch_builtin(scheme));
	//}
	if (execscheme_dispatch(scheme->rel_type[NEXT_R])(scheme) != 0)
	{
		dbg("%s\n", "Failed to execute scheme !");
		return (-1);
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
			return (-1);
		scheme = scheme->next;
		if (scheme && scheme->rel_type[PREV_R] & (REL_READ | REL_WRITE | REL_APPEND))
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

void	executor_kill_all(t_execscheme *scheme)
{
	while (scheme)
	{
		if (scheme->pid > 0)
		{
			p_signal(scheme->pid, SIGTERM);
			scheme->pid = -1;
		}
		scheme = scheme->next;
	}
}

int	execute(t_execscheme *rootscheme)
{
	int exitstatus;

	if (rootscheme == NULL)
		return (0);
	exitstatus = -1;
	if (executor_launch_processes(rootscheme) == 0)
		exitstatus = executor_get_exitstatus(rootscheme);
	executor_kill_all(rootscheme);
	return (exitstatus);
}
