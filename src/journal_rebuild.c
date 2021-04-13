/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   journal_rebuild.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:02:50 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:02:52 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "journal.h"

extern t_journal	*g_journal__;

void	journal_build_linked_list(void)
{
	const size_t		size = journal_size();
	ssize_t				index;
	t_token				*cur_token;
	t_token				*last_token;

	if (size == 0)
		return ;
	last_token = NULL;
	index = size - 1;
	while (index >= 0)
	{
		cur_token = journal_get(index);
		if ((size_t)index < size - 1)
		{
			cur_token->next = last_token;
			last_token = cur_token;
		}
		else
		{
			cur_token->next = NULL;
			last_token = cur_token;
		}
		cur_token->index = index;
		index--;
	}
}

void	journal_rebuild_tokens(void)
{
	size_t			i;
	t_token			*token;

	journal_reset_counters();
	i = 0;
	while (i < journal_size())
	{
		token = vector(&g_journal__->tokens, V_PEEKAT, i, 0);
		token->index = i;
		(g_journal__->counter)[token->type]++;
		i++;
	}
	journal_build_linked_list();
}
