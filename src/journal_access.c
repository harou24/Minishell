/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   journal_access.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:02:18 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:02:19 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "journal.h"

extern t_journal	*g_journal__;

t_vector	journal_get_token_vector(void)
{
	return (g_journal__->tokens);
}

char	*journal_get_string_for_token(t_token *token)
{
	if (token->string)
		return (ft_strdup(token->string));
	else
		return (ft_strsub(g_journal__->str,
				token->range.begin, 1 + token->range.end - token->range.begin));
}

char	*journal_get_string_for_index(size_t index)
{
	t_token				*token;

	token = journal_get(index);
	assert(token);
	return (journal_get_string_for_token(token));
}

void	journal_set_input_str(char *str)
{
	journal_clear_input_str();
	g_journal__->str = ft_strdup(str);
}

char	*journal_get_input_str(void)
{
	return (g_journal__->str);
}
