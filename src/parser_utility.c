/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utility.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:04:15 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:04:16 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <stdlib.h>

#include "debugger.h"
#include "libft.h"

#include "parser.h"

#define VEC_SIZE 128

extern t_parser	*g_parser__;

void	parse_flush_tokens(t_range area)
{
	size_t		len;

	len = area.begin;
	while (len > 0)
	{
		journal_remove(0);
		len--;
	}
	journal_rebuild_tokens();
}

t_vector	parse_get_subtokens(t_token *first, t_token *last)
{
	t_vector	subtokens;

	assert(first);
	assert(last);
	vector(&subtokens, V_CREATE, VEC_SIZE, NULL);
	if (!subtokens)
		return (NULL);
	while (first->next && first->next != last)
	{
		vector(&subtokens, V_PUSHBACK, 0, first->next);
		first = first->next;
	}
	return (subtokens);
}

void	parse_replace_tokens_with_token(t_vector tokens, t_token *first,
						t_token *last, t_token *token)
{
	const ssize_t	index_of_first = first->index;
	ssize_t			index;

	index = last->index;
	assert(index > 0);
	while (index >= index_of_first)
	{
		token_destroy(vector(&tokens, V_POPAT, index, NULL));
		index--;
	}
	if (index_of_first < (ssize_t)journal_size())
		vector(&tokens, V_PUSHAT, (size_t)index_of_first, token);
	else
		vector(&tokens, V_PUSHAT, journal_size(), token);
	assert(journal_size() > 0);
	journal_rebuild_tokens();
}

void	parser_set_env(t_env *env)
{
	assert(g_parser__);
	assert(! g_parser__->env);
	g_parser__->env = env;
}

void	parse_dump_match_area(t_range area)
{
	char	*range;
	char	*tokens;

	range = range_dump(area);
	tokens = journal_dump_tokens_for_range(area);
	dbg("area: %s, tokens: %s\n", range, tokens);
	free(range);
	free(tokens);
}
