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

static int	executor_launch_builtin(t_execscheme *scheme)
{
	return (command_dispatch(scheme->op_type)(scheme->cmd));
}

static t_bool	executor_is_builtin(t_execscheme *scheme)
{
	return (scheme->op_type != OP_COMMAND && scheme->op_type != OP_PATH);
}

static t_bool	executor_is_assignment(t_execscheme *scheme)
{
	return (scheme->op_type == OP_ASSIGNMENT);
}

int	executor_launch_sequential_scheme(t_execscheme *scheme, pid_t pid)
{
	static int pids_popped;

	if (scheme->rel_type[PREV_R] == REL_START)
		pids_popped = 0;
	if ((executor_is_builtin(scheme) || executor_is_assignment(scheme))
		&& !(scheme->rel_type[NEXT_R] & (REL_READ | REL_WRITE | REL_APPEND)))
	{
		dbg("LAUNCHING AT PARENT PROCESS!\n", "");
		p_signal(pid, SIGTERM);
		pids_popped++;
		return (executor_launch_builtin(scheme));
	}
	p_queue_wait_for_signals(p_tab_size() - pids_popped);
	p_signal(pid, SIGUSR1);
	return (p_waitpid(pid, W_EXITED));
}

void	executor_launch_parallel_scheme(pid_t pid)
{
	p_signal(pid, SIGUSR1);
}
