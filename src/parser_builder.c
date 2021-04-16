/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_builder.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:03:50 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:03:51 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>

#include "debugger.h"
#include "parser.h"

extern t_parser	*g_parser__;

/* this needs to fuck off out of this file */
t_bool	parse_keep_matching(void)
{
	return (g_parser__->matcharea.begin < g_parser__->matcharea.end);
}

char	*parse_build_argument(t_range *matcharea)
{
	t_token	*token;
	char	*arg;

	if (journal_at_index_is_type(matcharea->begin, SPACE))
		matcharea->begin++;
	arg = NULL;
	token = journal_get(matcharea->begin);
	while (token && matcharea->begin <= matcharea->end
		&& (token_is_alnum(token) || token_is_assignment(token) || token_is_escape(token)))
	{
		arg = ft_strjoin_noreuse(arg, journal_get_string_for_token(token));
		matcharea->begin++;
		token = journal_get(matcharea->begin);
	}
	return (arg);
}

char	*parse_build_path(t_range *matcharea)
{
	return (parse_build_argument(matcharea));
}
