#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "debugger.h"
#include "libft.h"

#include "filesystem.h"
#include "pipe.h"
#include "process.h"
#include "execscheme.h"
#include "executor.h"

#include <stdio.h>

int			handler_scheme_redirection(t_execscheme *scheme)
{
	pid_t	pid;
	pid_t	ppid;

	printf("HELLO\n");

	ppid = getpid();
	pid = fork();
	if (pid < 0)
	{
		/* error */
		dbg("Forking failed with error : %s\n", strerror(errno));
		abort();
		return (-1);
	}
	else if (pid == 0)
	{
		/* child */

		p_queue_register_signalhandler(SIGUSR1);
		dbg("new child with pid : %i\n", getpid());

		assert(scheme->next);
		assert(scheme->next->cmd);
		assert(scheme->next->cmd->path);

		if (scheme->rel_type[NEXT_R] & (REL_WRITE | REL_APPEND))
		{
			int fd;
			/* setup fd for writing/appending*/

			printf("opening path : %s\n", scheme->next->cmd->path);
			if (scheme->rel_type[NEXT_R] & REL_WRITE)
				fd = open("./test_f", O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else
				fd = open("./test_f", O_WRONLY | O_CREAT | O_APPEND, 0644);
				
			assert(fd != -1);
			dup2(fd, STDOUT);
			//close(fd);
		}
		else if (scheme->rel_type[NEXT_R] & REL_READ)
		{
			/* setup fd for reading */
			int fd = fs_open(scheme->next->cmd->path, O_RDONLY);
			assert(fd != -1);
			dup2(fd, STDIN);
			//close(fd);
		}

		/* duplicate and close read pipe from previous scheme */
		if (scheme->rel_type[PREV_R] == REL_PIPE)
		{
			if (!(scheme->rel_type[NEXT_R] & REL_READ))
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
	else
	{
		if (scheme->rel_type[PREV_R] == REL_PIPE)
		{
			close(scheme->prev->pipe[PIPE_READ]);
			close(scheme->prev->pipe[PIPE_WRITE]);
		}

		/* parent */
		return ((p_tab_push(pid) == TRUE) ? 0 : -1);
	}
	return (-1);
}
