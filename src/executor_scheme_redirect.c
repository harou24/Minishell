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

t_bool	redirection_stdout_to_pipe(const char *fname,
						t_bool should_append)
{
	int			fd;

	if (should_append)
		fd = open(fname, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		dbg("Failing opening file{%s} for dupping to stdout, errno %s\n",
			fname, strerror(errno));
		return (FALSE);
	}
	if (dup2(fd, STDOUT) == -1)
	{
		dbg("Failing dupping to stdout, errno %s\n", strerror(errno));
		close(fd);
		return (FALSE);
	}
	close (fd);
	return (TRUE);
}

t_bool	redirection_file_to_stdin(const char *fname)
{
	int			fd;

	fd = fs_open(fname, O_RDONLY);
	if (fd == -1)
	{
		dbg("Failing opening file{%s} for dupping to stdin, errno %s\n",
			fname, strerror(errno));
		return (FALSE);
	}
	if (dup2(fd, STDIN) == -1)
	{
		dbg("Failing dupping stdin, errno %s\n", strerror(errno));
		close(fd);
		return (FALSE);
	}
	close(fd);
	return (TRUE);
}

t_bool	redirection_pipe_to_stdin(int pipe[2])
{
	if (dup2(pipe[PIPE_READ], STDIN) == -1)
	{
		dbg("Failing dupping stdin, errno %s\n", strerror(errno));
		return (FALSE);
	}
	drop_pipe(pipe);
	return (TRUE);
}

static void	child(t_execscheme *scheme)
{
	int	exitstatus;

	if (scheme->rel_type[NEXT_R] & (REL_WRITE | REL_APPEND))
	{
		if (!redirection_stdout_to_pipe(scheme->next->cmd->path,
				scheme->rel_type[NEXT_R] & REL_APPEND))
			exit (1);
	}
	else if (scheme->rel_type[NEXT_R]
		& REL_READ && scheme->rel_type[PREV_R] != REL_PIPE)
	{
		if (!redirection_file_to_stdin(scheme->next->cmd->path))
			exit(1);
	}
	if (scheme->rel_type[PREV_R] == REL_PIPE)
	{
		if (!redirection_pipe_to_stdin(scheme->prev->pipe))
			exit (1);
	}
	exitstatus = command_dispatch(scheme->op_type)(scheme->cmd);
	dbg("FATAL: child process didn't exit! errno: %s\n", strerror(errno));
	exit (exitstatus);
}

static int	run_in_parent(t_execscheme *scheme)
{
	int	exitstatus;

	if (scheme->rel_type[NEXT_R] & (REL_WRITE | REL_APPEND))
	{
		if (! redirection_stdout_to_pipe(scheme->next->cmd->path,
				scheme->rel_type[NEXT_R] & REL_APPEND))
			return (1);
	}
	else if (scheme->rel_type[NEXT_R]
		& REL_READ && scheme->rel_type[PREV_R] != REL_PIPE)
	{
		if (!redirection_file_to_stdin(scheme->next->cmd->path))
			return (1);
	}
	if (scheme->rel_type[PREV_R] == REL_PIPE)
	{
		if (!redirection_pipe_to_stdin(scheme->prev->pipe))
			return (1);
	}
	exitstatus = command_dispatch(scheme->op_type)(scheme->cmd);
	return (exitstatus);
}

static int	parent(t_execscheme *scheme, pid_t childprocess)
{
	if (scheme->rel_type[PREV_R] == REL_PIPE)
		drop_pipe(scheme->prev->pipe);
	scheme->pid = childprocess;
	return (0);
}

int	handler_scheme_redirection(t_execscheme *scheme)
{
	pid_t	pid;

	dbg("PICKING UP REDIRECTION SCHEME!\n", "");
	if (!scheme->next || (scheme->rel_type[NEXT_R]
			& REL_READ && !fs_exists(scheme->next->cmd->path)))
		return (-1);
	if (executor_should_run_in_parent(scheme))
		return (run_in_parent(scheme));
	pid = fork();
	if (pid < 0)
	{
		dbg("Forking failed with error : %s\n", strerror(errno));
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
