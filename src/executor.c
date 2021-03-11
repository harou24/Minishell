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

	error = 0;
	while (scheme)
	{
		/*
			1. handle op type
			2. setup fd's
			3. fork()
			4. execute
		*/
		pid = fork();
		if (pid == 0)
		{
			/* child */
			/*g_optab__[scheme->op_type](scheme->cmd); */
			dbg("%s\n", "child process didn't exit!");
			abort();
		}
		else
		{
			/* parent */
			/* store pid in vec */
			pid_push(pid_allocate(pid));
		}

		/* handle error */
	
		/* if REL_SEQ -> wait for pid to finish, this is very slow -> wait in child process! */
		if (scheme->relation_type == REL_SEQ)
			pid_wait(pid);

		scheme = scheme->next;
	}
	/* wait for all child processes to finish,  or kill processes when process returns non-zero */
	error = pid_wait_all();
	pid_kill_all();
	return (error);
}
