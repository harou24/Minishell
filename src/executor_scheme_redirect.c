#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "debugger.h"
#include "libft.h"

#include "filesystem.h"
#include "ft_unistd.h"
#include "process.h"
#include "execscheme.h"
#include "executor.h"

#define CHILD 0

static t_bool	redirection_write_handle_fd(const char *fname, t_bool should_append)
{
	int			fd;
	t_bool		success;

	assert(fname);
	success = FALSE;
	if (should_append)
		fd = open(fname, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		
	if (fd != -1)
	{
		success = (dup2(fd, STDOUT) != -1);
		close(fd);
	}
	return (success);
}

static t_bool	redirection_read_handle_fd(const char *fname)
{
	int			fd;
	t_bool		success;

	assert(fname);
	success = FALSE;
	fd = fs_open(fname, O_RDONLY);
	if (fd != -1)
	{
		success = (dup2(fd, STDIN) != -1);
		close(fd);
	}
	return (success);
}

int			handler_scheme_redirection(t_execscheme *scheme)
{
	pid_t	pid;
	pid_t	ppid;

	if (!scheme->next)
		return (-1);
	if (scheme->rel_type[NEXT_R] & REL_READ && !fs_exists(scheme->next->cmd->path))
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
		p_queue_register_signalhandler(SIGUSR1);

		assert(scheme->next);
		assert(scheme->next->cmd);
		assert(scheme->next->cmd->path);

		if (scheme->rel_type[NEXT_R] & (REL_WRITE | REL_APPEND))
		{
			if (!redirection_write_handle_fd(scheme->next->cmd->path,
					scheme->rel_type[NEXT_R] & REL_APPEND))
				exit (1);
		}
		else if (scheme->rel_type[NEXT_R] & REL_READ)
		{
			if(!redirection_read_handle_fd(scheme->next->cmd->path))
				exit (1);
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
