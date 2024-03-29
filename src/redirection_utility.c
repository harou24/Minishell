/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection_utility.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 20:56:10 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 20:56:17 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <stdlib.h>
#include <errno.h>

#include "libft.h"
#include "debugger.h"

#include "redirection.h"

char	*redir_get(t_redirection *redir, t_redirection_type type, size_t index)
{
	assert(redir);
	return ((char *)vector(&redir->vec[type], V_PEEKAT, index, NULL));
}

t_bool	redir_push(t_redirection *redir, t_redirection_type type, char *fname)
{
	assert(redir);
	return (vector(&redir->vec[type], V_PUSHBACK, 0, fname) != NULL);
}

size_t	redir_get_size(t_redirection *redir, t_redirection_type type)
{
	assert(redir);
	return (*(size_t *)vector(&redir->vec[type], V_SIZE, 0, NULL));
}
