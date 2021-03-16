#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "debugger.h"
#include "libft.h"

#include "process.h"
#include "execscheme.h"
#include "executor.h"

#include <stdio.h>

int			handler_scheme_seq(t_execscheme **scheme)
{
	pid_t	pid;
	pid_t	ppid;

	ppid = getpid();
	pid = fork();
	if (pid < 0)
	{
		/* error */
		dbg("Forking failed with error : %s\n", strerror(errno));
		return (-1);
	}
	else if (pid == 0)
	{
		/* child */

		p_queue_register_signalhandler(SIGUSR1);

		dbg("new child with pid : %i\n", getpid());

		/* send a signal to parent, indicating ready to start */
		p_signal(ppid, SIGUSR1);

		/* wait for single signal */
		p_queue_wait_for_signals(1);

		command_dispatch((*scheme)->op_type)((*scheme)->cmd);
		dbg("FATAL: child process didn't exit! errno: %s\n", strerror(errno));
		abort();
	}
	else
	{
		/* parent */
		return ((p_tab_push(pid) == TRUE) ? 0 : -1);
	}
	return (-1);
}
