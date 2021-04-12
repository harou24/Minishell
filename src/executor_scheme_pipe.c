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

static void	child(t_execscheme *scheme)
{
	int	exitstatus;

	if (dup2(scheme->pipe[PIPE_WRITE], STDOUT) == -1)
		exit (1);
	drop_pipe(scheme->pipe);
	if (scheme->rel_type[PREV_R] == REL_PIPE)
	{
		if (!redirection_pipe_to_stdin(scheme->prev->pipe))
			exit (1);
	}
	exitstatus = command_dispatch(scheme->op_type)(scheme->cmd);
	dbg("FATAL: child process didn't exit! errno: %s\n", strerror(errno));
	exit (exitstatus);
}

static int	parent(t_execscheme *scheme, pid_t childprocess)
{
	if (scheme->rel_type[PREV_R] == REL_PIPE)
		close(scheme->prev->pipe[PIPE_WRITE]);
	scheme->pid = childprocess;
	return (0);
}

int	handler_scheme_pipe(t_execscheme *scheme)
{
	pid_t			pid;

	 dbg("PICKING UP PIPE SCHEME!\n", "");
	if (pipe(scheme->pipe) == -1)
	{
		dbg("Pipe syscall failed with error : %s\n", strerror(errno));
		return (-1);
	}
	pid = fork();
	if (pid < 0)
	{
		dbg("Forking failed with error : %s\n", strerror(errno));
		drop_pipe(scheme->pipe);
		return (-1);
	}
	else if (pid == CHILD)
	{
		child(scheme);
		exit(1);
	}
	else
		return (parent(scheme, pid));
}
