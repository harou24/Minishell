/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
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

static const t_redirection_type	g_redirection_tab__[TOKEN_TYPE_SIZE] = {
					[LEFTSHIFT] = RED_READ,
					[DOUBLERIGHTSHIFT] = RED_APPEND,
					[RIGHTSHIFT] = RED_WRITE,
				};

t_redirection_type redir_get_type_for_token(t_token *token)
{
	if (token->type >= TOKEN_TYPE_SIZE)
	{
		errno = ERANGE;
		return (RED_NO_TYPE);
	}
	return (g_redirection_tab__[token->type]);
}

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

t_bool	redir_perform_redirection(t_redirection *redir, t_redirection_type type, size_t index)
{
	if (type == RED_APPEND)
		return (redir_stdout_to_file(redir_get(redir, type, index), TRUE));
	if (type == RED_WRITE)
		return (redir_stdout_to_file(redir_get(redir, type, index), FALSE));
	if (type == RED_READ)
		return (redir_file_to_stdin(redir_get(redir, type, index)));
	return (FALSE);
}

t_bool	redir_perform_redirections(t_redirection *redir)
{
	size_t	type_i;
	size_t	size;

	type_i = 0;
	while (type_i < RED_TAB_SIZE)
	{
		size = redir_get_size(redir, type_i);
		if (size > 0)
		{
			if (!redir_perform_redirection(redir, type_i, size - 1))
				return (FALSE);
		}
		type_i++;
	}
	return (TRUE);
}

t_bool	redir_has_redirections(t_redirection *redir)
{
	size_t	type_i;

	type_i = 0;
	while (type_i < RED_TAB_SIZE)
	{
		if (redir_get_size(redir, type_i) > 0 )
			return (TRUE);
		type_i++;
	}
	return (FALSE);
}

t_redirection	*redir_create(void)
{
	const size_t	vec_size = 16;
	t_redirection	*redir;
	size_t			type_i;

	redir = ft_calloc(sizeof(t_redirection), 1);
	if (redir)
	{
		type_i = 0;
		while (type_i < RED_TAB_SIZE)
		{
			if (!vector(&redir->vec[type_i], V_CREATE, vec_size, NULL))
			{
				redir_destroy(&redir);
				return (NULL);
			}
			type_i++;
		}
	}
	return (redir);
}

t_redirection	*redir_destroy(t_redirection **redir)
{
	size_t		type_i;

	if (!redir)
		return (NULL);
	if (*redir)
	{
		type_i = 0;
		while (type_i < RED_TAB_SIZE)
		{
			if ((*redir)->vec[type_i])
				vector(&(*redir)->vec[type_i], V_DESTROY, TRUE, NULL);
			type_i++;
		}
		free(*redir);
	}
	return ((*redir = NULL));
}
