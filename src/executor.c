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

int	executor_launch_sequential_scheme(t_execscheme *scheme, pid_t pid)
{
	assert(pid != -1);
	if (executor_is_builtin(scheme)
		&& !(scheme->rel_type[NEXT_R] & (REL_READ | REL_WRITE | REL_APPEND)))
	{
		p_signal(pid, SIGTERM);
		return (executor_launch_builtin(scheme));
	}
	p_signal(pid, SIGUSR1);
	return (p_waitpid(pid, W_EXITED));
}

void	executor_launch_parallel_scheme(pid_t pid)
{
	assert(pid != -1);
	p_signal(pid, SIGUSR1);
}
