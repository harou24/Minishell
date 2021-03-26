#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "debugger.h"
#include "libft.h"

#include "ft_unistd.h"
#include "process.h"
#include "execscheme.h"
#include "executor.h"

#define CHILD 0

int			handler_scheme_seq(t_execscheme *scheme)
{
	pid_t	pid;
	pid_t	ppid;

	ppid = getpid();
	pid = fork();
	if (pid < 0)
	{
		dbg("Forking failed with error : %s\n", strerror(errno));
		return (-1);
	}
	else if (pid == CHILD)
	{
		p_queue_register_signalhandler(SIGUSR1);

		/* duplicate and close read pipe from previous scheme */
		if (scheme->rel_type[PREV_R] == REL_PIPE)
		{
			assert(dup2(scheme->prev->pipe[PIPE_READ], STDIN) != -1);
			close(scheme->prev->pipe[PIPE_READ]);
			close(scheme->prev->pipe[PIPE_WRITE]);
		}

		/* send a signal to parent, indicating ready to start */
		p_signal(ppid, SIGUSR1);

		/* wait for single signal */
		p_queue_wait_for_signals(1);

		command_dispatch(scheme->op_type)(scheme->cmd);
		dbg("FATAL: child process didn't exit! errno: %s\n", strerror(errno));
		abort();
	}
	else /* parent */
	{
		if (scheme->rel_type[PREV_R] == REL_PIPE)
		{
			close(scheme->prev->pipe[PIPE_READ]);
			close(scheme->prev->pipe[PIPE_WRITE]);
		}
		return ((p_tab_push(pid) == TRUE) ? 0 : -1);
	}
	return (-1);
}
