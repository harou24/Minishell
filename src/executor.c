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

int			executor_launch_sequential_scheme(t_execscheme *scheme, pid_t pid)
{
	assert(pid != -1);
	p_signal(pid, SIGUSR1);
	return(p_waitpid(pid, W_EXITED));
	(void)scheme;
}

void		executor_launch_parallel_scheme(pid_t pid)
{
	assert(pid != -1);
	p_signal(pid, SIGUSR1);
}

int			executor_launch_processes(t_execscheme *scheme)
{
	int		error;
	size_t	pid_index;

	error = 0;
	pid_index = 0;
	while (scheme)
	{
		if (scheme->rel_type[NEXT_R] == REL_PIPE)
		{
			/* parallel operation */
			executor_launch_parallel_scheme(p_tab_at(pid_index));
			pid_index++;
		}
		else if (!(scheme->rel_type[PREV_R] & (REL_READ | REL_APPEND | REL_WRITE)))
		{
			/* sequential operation */
			error = executor_launch_sequential_scheme(scheme, p_tab_at(pid_index));
			pid_index++;
		}
		scheme = scheme->next;
	}
	return (error);
}

int		executor_prepare_processes(t_execscheme *scheme)
{
	while (scheme)
	{
		/* dispatch for execscheme type */
		if (!(scheme->rel_type[PREV_R] & (REL_READ | REL_APPEND | REL_WRITE)))
		{
			dbg("executing scheme: %s, %s <- relation -> %s\n", execscheme_dump_op_type(scheme->op_type), execscheme_dump_relation_type(scheme->rel_type[PREV_R]), execscheme_dump_relation_type(scheme->rel_type[NEXT_R]));
			if (execscheme_dispatch(scheme->rel_type[NEXT_R])(scheme) != 0)
			{
				dbg("%s\n", "failed to prepare scheme !");
				p_tab_signal_all(SIGTERM);
				return (-1);
			}
		}
		scheme = scheme->next;
	}
	return (0);
}

int			execute(t_execscheme *scheme)
{
	int		error;

	error = 0;
	p_queue_register_signalhandler(SIGUSR1);

	if ((error = executor_prepare_processes(scheme)) == 0)
	{
		/* wait for children to register signal handlers */
		p_queue_wait_for_signals(p_tab_size());
		error = executor_launch_processes(scheme);
	}

	/* kill the kids */
	p_tab_signal_all(SIGTERM);
	return (error);
}
