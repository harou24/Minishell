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
	p_queue_register_signalhandler(SIGUSR1);
	dbg("REGISTERED FOR SIGUSR1 SIGNAL\n%s", "");
	if (scheme->rel_type[PREV_R] == REL_PIPE)
	{
		if (dup2(scheme->prev->pipe[PIPE_READ], STDIN) == -1)
		{
			dbg("ERRNO->%s, fd->%d\n",
				strerror(errno), scheme->prev->pipe[PIPE_READ]);
			exit (1);
		}
		close(scheme->prev->pipe[PIPE_READ]);
		close(scheme->prev->pipe[PIPE_WRITE]);
	}
	dbg("SENDING SIGUSR1 SIGNAL\n%s", "");
	//usleep(100);
	p_signal(ppid, SIGUSR1);
	dbg("WAITING FOR SIGNAL\n%s", "");
	p_queue_wait_for_signals(1);
	dbg("GOT SIGNAL\n%s", "");
	command_dispatch(scheme->op_type)(scheme->cmd);
	dbg("FATAL: child process didn't exit! errno: %s\n", strerror(errno));
}

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
		exec_child_process(scheme, ppid);
	else
	{
		if (scheme->rel_type[PREV_R] == REL_PIPE)
		{
			close(scheme->prev->pipe[PIPE_READ]);
			close(scheme->prev->pipe[PIPE_WRITE]);
		}
		if (p_tab_push(pid) == TRUE)
			return (0);
		else
			return (-1);
	}
	return (-1);
}
