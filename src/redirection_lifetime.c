/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection_lifetime.c                             :+:    :+:            */
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
