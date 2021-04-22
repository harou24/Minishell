/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_istype.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:04:11 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:04:13 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <stdlib.h>

#include "debugger.h"
#include "libft.h"

#include "token.h"

t_bool	token_is_assignment(t_token *token)
{
	return (token && token->type == ASSIGNMENT);
}

t_bool	token_is_escape(t_token *token)
{
	return (token && token->type == ESCAPE);
}

t_bool	token_is_escape_space(t_token *token)
{
	return (token && token->type == ESCAPE_SPACE);
}

t_bool	token_is_valid_argument(t_token *token)
{
	return (token_is_alnum(token)
		|| token_is_assignment(token)
		|| token_is_escape(token)
		|| token_is_escape_space(token));
}
