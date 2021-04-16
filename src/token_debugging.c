/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_debugging.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:08:28 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:08:31 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static const char	*token_dump_type_continue(t_token_type_e type)
{
	if (type == NEWLINE)
		return ("NEWLINE");
	if (type == SEMICOLON)
		return ("SEMICOLON");
	if (type == LEFTSHIFT)
		return ("READ");
	if (type == RIGHTSHIFT)
		return ("WRITE");
	if (type == DOUBLERIGHTSHIFT)
		return ("APPEND");
	if (type == NULLBYTE)
		return ("NULLBYTE");
	if (type == NO_TYPE)
		return ("NO_TYPE");
	return ("UNKNOWN");
}

const char	*token_dump_type(t_token_type_e type)
{
	if (type == WORD)
		return ("WORD");
	if (type == SYM)
		return ("SYM");
	if (type == STRING)
		return ("STRING");
	if (type == LITERAL)
		return ("LITERAL");
	if (type == ASSIGNMENT)
		return ("ASSIGNMENT");
	if (type == ESCAPE)
		return ("ESCAPE");
	if (type == VARIABLE)
		return ("VARIABLE");
	if (type == SPACE)
		return ("SPACE");
	if (type == ESCAPE_SPACE)
		return ("ESCAPE_SPACE");
	if (type == PIPE)
		return ("PIPE");
	return (token_dump_type_continue(type));
}
