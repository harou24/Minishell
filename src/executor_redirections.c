/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_redirects.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:01:17 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:01:19 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "debugger.h"
#include "libft.h"

#include "filesystem.h"
#include "ft_unistd.h"
#include "executor.h"

t_bool	executor_handle_redirections_pre(t_execscheme *scheme)
{
	redir_std_push();
	if (scheme->rel_type[PREV_R] == REL_PIPE && !redir_pipe_to_stdin(scheme->prev->pipe))
		return (FALSE);
	if (scheme->rel_type[NEXT_R] == REL_PIPE && !redir_stdout_to_pipe(scheme->pipe))
		return (FALSE);
	if (redir_has_redirections(scheme->redir) && !redir_perform_redirections(scheme->redir))
		return (FALSE);
	if (scheme->prev)
		drop_pipe(scheme->prev->pipe);
	drop_pipe(scheme->pipe);
	return (TRUE);
}

t_bool	executor_handle_redirections_post(t_execscheme *scheme)
{
	redir_std_pop();
	(void)scheme;
	return (TRUE);
}

/*
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

	redirection_std_push();
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
	redirection_std_pop();
	return (exitstatus);
}


int	handler_scheme_redirection(t_execscheme *scheme)
{
	(void)scheme;
	abort();
	return (-1);
	pid_t	pid;

	if (!scheme->next || (scheme->rel_type[NEXT_R]
			& REL_READ && !fs_exists(scheme->next->cmd->path)))
		return (-1);
}
*/
