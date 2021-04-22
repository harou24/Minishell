/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_scheme_seq.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:01:23 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:01:24 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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

	if (!executor_handle_redirections_pre(scheme))
		exit (-1);
	exitstatus = command_dispatch(scheme->op_type)(scheme->cmd);
	dbg("FATAL: child process didn't exit! errno: %s\n", strerror(errno));
	exit (exitstatus);
}

static int	run_in_parent(t_execscheme *scheme)
{
	int	exitstatus;

	if (!executor_handle_redirections_pre(scheme))
		return (-1);
	exitstatus = command_dispatch(scheme->op_type)(scheme->cmd);
	if (!executor_handle_redirections_post(scheme))
		return (-1);
	return (exitstatus);
}

static int	parent(t_execscheme *scheme, pid_t childprocess)
{
	if (scheme->rel_type[PREV_R] == REL_PIPE)
		drop_pipe(scheme->prev->pipe);
	scheme->pid = childprocess;
	return (0);
}

int	handler_scheme_seq(t_execscheme *scheme)
{
	pid_t	pid;

	if (executor_should_run_in_parent(scheme))
		return (run_in_parent(scheme));
	pid = fork();
	if (pid == -1)
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
