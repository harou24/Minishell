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

static t_bool	redirection_write_handle_fd(const char *fname,
						t_bool should_append)
{
	int			fd;
	t_bool		success;

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

	success = FALSE;
	fd = fs_open(fname, O_RDONLY);
	if (fd != -1)
	{
		success = (dup2(fd, STDIN) != -1);
		close(fd);
	}
	return (success);
}

static void	exec_child_process(t_execscheme *scheme, pid_t ppid)
{
	p_queue_register_signalhandler(SIGUSR1);
	dbg("REGISTERED FOR SIGUSR1 SIGNAL\n%s", "");
	if (scheme->rel_type[NEXT_R] & (REL_WRITE | REL_APPEND))
	{
		if (!redirection_write_handle_fd(scheme->next->cmd->path,
				scheme->rel_type[NEXT_R] & REL_APPEND))
			exit (1);
	}
	else if (scheme->rel_type[NEXT_R] & REL_READ)
	{
		if (!redirection_read_handle_fd(scheme->next->cmd->path))
			exit (1);
	}
	if (scheme->rel_type[PREV_R] == REL_PIPE)
	{
		if (!(scheme->rel_type[NEXT_R] & REL_READ))
			if (dup2(scheme->prev->pipe[PIPE_READ], STDIN) == -1)
				exit (1);
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

static void	exec_parent_process(t_execscheme *scheme)
{
	if (scheme->rel_type[PREV_R] == REL_PIPE)
	{
		close(scheme->prev->pipe[PIPE_READ]);
		close(scheme->prev->pipe[PIPE_WRITE]);
	}
}

int	handler_scheme_redirection(t_execscheme *scheme)
{
	pid_t	pid;
	pid_t	ppid;

	if (!scheme->next || (scheme->rel_type[NEXT_R]
			& REL_READ && !fs_exists(scheme->next->cmd->path)))
		return (-1);
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
		exec_parent_process(scheme);
		p_tab_push(pid);
		return (0);
	}
	return (-1);
}
