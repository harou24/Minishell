/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_lookup.c                                    :+:    :+:            */
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

#include "parser.h"

extern t_parser	*g_parser__;

t_bool	parse_is_token_in_matcharea(t_token *token)
{
	return (token && token->index <= g_parser__->matcharea.end);
}
