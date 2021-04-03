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

static void	exec_child_process(t_execscheme *scheme, pid_t ppid)
{
	assert(dup2(scheme->pipe[PIPE_WRITE], STDOUT) != -1);
	close(scheme->pipe[PIPE_WRITE]);
	close(scheme->pipe[PIPE_READ]);
	if (scheme->rel_type[PREV_R] == REL_PIPE)
	{
		assert(dup2(scheme->prev->pipe[PIPE_READ], STDIN) != -1);
		close(scheme->prev->pipe[PIPE_READ]);
		close(scheme->prev->pipe[PIPE_WRITE]);
	}
	p_queue_register_signalhandler(SIGUSR1);
	p_signal(ppid, SIGUSR1);
	p_queue_wait_for_signals(1);
	command_dispatch(scheme->op_type)(scheme->cmd);
	dbg("FATAL: child process didn't exit! errno: %s\n", strerror(errno));
	abort();
}

static void	exec_parent_process(t_execscheme *scheme)
{
	if (scheme->rel_type[PREV_R] == REL_PIPE)
	{
		close(scheme->prev->pipe[PIPE_READ]);
		close(scheme->prev->pipe[PIPE_WRITE]);
	}
}

int	handler_scheme_pipe(t_execscheme *scheme)
{
	pid_t			pid;
	pid_t			ppid;

	if (pipe(scheme->pipe) == -1)
		return (-1);
	ppid = getpid();
	pid = fork();
	if (pid < 0)
	{
		dbg("Forking failed with error : %s\n", strerror(errno));
		return (-1);
	}
	else if (pid == CHILD)
	{
		exec_child_process(scheme, ppid);
	}
	else
	{
		exec_parent_process(scheme);
		if (p_tab_push(pid) == TRUE)
			return (0);
		else
			return (-1);
	}
	return (-1);
}
