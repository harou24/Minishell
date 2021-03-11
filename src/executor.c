#include <assert.h>
#include <stdlib.h>

#include <sys/wait.h>
#include <unistd.h>

#include "libft.h"
#include "debugger.h"

#include "command.h"
#include "pid.h"
#include "executor.h"

#include "bash_ops.h"

int		execute(t_execscheme *scheme)
{
	int		error;
	pid_t	pid;
	pid_t	pid_prev;

	error = 0;
	while (scheme)
	{
		/*
			1. handle op type
			2. setup fd's
			3. fork()
			4. execute
		*/


		/* prepare execscheme */
		if (!exec_prepare_execscheme_dispatch(scheme->relation_type)(scheme))
		{
			/* failed to prepare execscheme */
		}

		pid_prev = pid_last();
		pid = fork();
		if (pid == 0)
		{
			/* child */
			if (scheme->prev && scheme->prev->relation_type == REL_SEQ)
				pid_wait(pid_prev);
			
			/* call command */
			exec_command_dispatch(scheme->op_type)(scheme->cmd);
			dbg("%s\n", "child process didn't exit!");
			abort();
		}
		else
		{
			/* parent */

			/* store pid in vec */
			pid_push(pid_allocate(pid));
		}
		scheme = scheme->next;
	}

	/* wait for all child processes to finish,  or kill processes when process returns non-zero */
	error = pid_wait_all();
	pid_kill_all();
	return (error);
}
