/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   preparser.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:04:28 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:04:30 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <stdlib.h>

#include "libft.h"

#include "debugger.h"
#include "bash_pattern.h"
#include "parser.h"
#include "env_singleton.h"
#include "journal.h"

static void	remove_redundant_semicolons(void)
{
	while (journal_get(0) && journal_get(0)->type == SEMICOLON)
		journal_remove(0);
	journal_rebuild_tokens();
}

static int	num_tokens_of_type_in_range(t_token_type_e type, t_range area)
{
	int		num;
	t_token	*token;

	num = 0;
	token = journal_find_nth_type(type, num);
	while (token && token->index >= area.begin && token->index < area.end)
	{
		num++;
		token = journal_find_nth_type(type, num);
	}
	return (num);
}

static t_bool	area_has_unfinished_string(t_range area)
{
	return (num_tokens_of_type_in_range(STRING, area) % 2 != 0
		|| num_tokens_of_type_in_range(LITERAL, area) % 2 != 0);
}

t_range	preparser_get_next_area(void)
{
	t_token			*token;
	t_range			matchrange;

	remove_redundant_semicolons();
	matchrange = range(0, 0);
	token = journal_get(matchrange.end);
	while (token)
	{
		if (token->type == SEMICOLON || token->type == NULLBYTE)
		{
			if (token->type != SEMICOLON
				|| !area_has_unfinished_string(range(matchrange.begin,
						matchrange.end + 1)))
				return (range(matchrange.begin, matchrange.end + 1));
		}
		matchrange.end++;
		token = journal_get(matchrange.end);
	}
	return (range(0, 0));
}
