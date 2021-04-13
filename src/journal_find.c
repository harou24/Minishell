#include <assert.h>
#include "journal.h"

extern t_journal	*g_journal__;

t_token	*journal_find_nth_type(const e_token_type type, int n)
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

t_token	*journal_find_first_type(const e_token_type type)
{
	return (journal_find_nth_type(type, 0));
}

t_token	*journal_find_last_type(const e_token_type type)
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
