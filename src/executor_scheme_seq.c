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
#include "ft_printf.h"
int	handler_scheme_seq(t_execscheme *scheme)
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
		if (scheme->rel_type[PREV_R] == REL_PIPE)
		{
			if (dup2(scheme->prev->pipe[PIPE_READ], STDIN) == -1)
			{
				ft_printf("ERRNO->%s, fd->%d\n", strerror(errno), scheme->prev->pipe[PIPE_READ]);
			}
			close(scheme->prev->pipe[PIPE_READ]);
			close(scheme->prev->pipe[PIPE_WRITE]);
		}
		p_signal(ppid, SIGUSR1);
		p_queue_wait_for_signals(1);
		command_dispatch(scheme->op_type)(scheme->cmd);
		dbg("FATAL: child process didn't exit! errno: %s\n", strerror(errno));
		abort();
	}
	else
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
