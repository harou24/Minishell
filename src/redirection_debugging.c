/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection_debugging.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:00:51 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:00:53 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>

#include "debugger.h"
#include "redirection.h"

const char	*redir_dump_type(t_redirection_type type)
{
	if (type == RED_READ)
		return ("READ");
	if (type == RED_APPEND)
		return ("APPEND");
	if (type == RED_WRITE)
		return ("WRITE");
	return ("NO_TYPE");
}

void redir_pretty_dump_for_type(t_redirection *redir, t_redirection_type type, int indent)
{
	size_t	i;
	
	i = 0;
	while (i < redir_get_size(redir, type))
	{
		dbg("%*s{%lu}: %s\n", (int)(indent + 1), redir_dump_type(type)
			, i, redir_get(redir, type, i));
		i++;
	}
	if (i == 0)
	{
		dbg("%*s : %s\n", (int)(indent + 1)
			, redir_dump_type(type), "NO REDIRECTION");
	}
}

void	redir_pretty_dump(t_redirection *redir, int indent)
{
	assert(redir);
	if (redir)
	{
		dbg("%*s:\n", indent, "Redirection ");
		redir_pretty_dump_for_type(redir, RED_READ, indent);
		redir_pretty_dump_for_type(redir, RED_WRITE, indent);
		redir_pretty_dump_for_type(redir, RED_APPEND, indent);
	}
}
