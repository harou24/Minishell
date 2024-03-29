/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   journal_find.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:02:35 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:02:36 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "journal.h"

extern t_journal	*g_journal__;

t_token	*journal_find_nth_type(const t_token_type_e type, int n)
{
	const size_t		size = journal_size();
	size_t				index;
	t_token				*cur_token;

	index = 0;
	while (index < size)
	{
		cur_token = journal_get(index);
		assert(cur_token);
		if (cur_token->type == type)
		{
			if (n == 0)
				return (cur_token);
			n--;
		}
		index++;
	}
	return (NULL);
}

t_token	*journal_find_first_token(const t_token *token)
{
	return (journal_find_first_type(token->type));
}

t_token	*journal_find_last_token(const t_token *token)
{
	return (journal_find_last_type(token->type));
}

t_token	*journal_find_first_type(const t_token_type_e type)
{
	return (journal_find_nth_type(type, 0));
}

t_token	*journal_find_last_type(const t_token_type_e type)
{
	const size_t		size = journal_size();
	ssize_t				index;
	t_token				*cur_token;

	if (size == 0)
		return (NULL);
	index = size - 1;
	while (index >= 0)
	{
		cur_token = journal_get(index);
		if (cur_token->type == type)
			return (cur_token);
		index--;
	}
	return (NULL);
}
