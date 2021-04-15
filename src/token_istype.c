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

t_bool	token_is_variable(t_token *token)
{
	return (token && token->type == VARIABLE);
}

t_bool	token_is_redirection(t_token *token)
{
	return (token &&
		(token->type == LEFTSHIFT
		|| token->type == RIGHTSHIFT
		|| token->type == DOUBLERIGHTSHIFT)
		);
}

t_bool	token_is_relation(t_token *token)
{
	return (token &&
		(token->type == SEMICOLON
		|| token->type == PIPE
		|| token->type == NULLBYTE)
		);
}

t_bool	token_is_alnum(t_token *token)
{
	return (token &&
		(token->type == WORD
		|| token->type == SYM)
		);
}

t_bool	token_is_space(t_token *token)
{
	return (token && token->type == SPACE);
}

t_bool	token_is_assignment(t_token *token)
{
	return (token && token->type == ASSIGNMENT);
}
