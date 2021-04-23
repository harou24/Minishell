/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_extraction.c                                :+:    :+:            */
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

t_bool	parse_extract_redirection(t_redirection *redir, t_range *area)
{
	char				*arg;
	t_redirection_type	type;

	if (token_is_redirection(journal_get(area->begin)))
	{
		type = redir_get_type_for_token(journal_get(area->begin));
		area->begin++;
		arg = parse_build_argument(area);
		assert(arg);
		return (redir_push(redir, type, arg));
	}
	return (TRUE);
}

t_bool	parse_extract_arguments(t_command *cmd, t_range *area)
{
	char	*arg;

	if (token_is_valid_argument(journal_get(area->begin)))
	{
		arg = parse_build_argument(area);
		assert(arg);
		return (command_push_argument(cmd, arg));
	}
	return (TRUE);
}

t_bool	parse_extract_command_arguments(
			t_redirection *redir,
			t_command *cmd,
			t_range area)
{
	t_token	*token;

	token = journal_get(area.begin);
	while (token && !token_is_relation(token) && area.begin <= area.end)
	{
		if (!parse_extract_redirection(redir, &area))
			return (FALSE);
		if (!parse_extract_arguments(cmd, &area))
			return (FALSE);
		area.begin++;
		token = journal_get(area.begin);
	}
	return (TRUE);
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
		&& token_is_valid_argument(token))
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
