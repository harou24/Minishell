#include <assert.h>
#include "journal.h"

extern t_journal	*g_journal__;

t_token	*journal_push(t_token *token)
{
	assert(token->type < TOKEN_TYPE_SIZE);
	if (vector(&g_journal__->tokens, V_PUSHBACK, 0, token))
	{
		(g_journal__->counter)[token->type]++;
		return (token);
	}
	else
	{
		return (NULL);
	}
}

t_token	*journal_get(size_t index)
{
	if (index >= journal_size())
		return (NULL);
	else
		return (vector(&g_journal__->tokens, V_PEEKAT, index, NULL));
}

t_bool	journal_remove(size_t index)
{
	t_token				*token;

	if (index < journal_size())
	{
		token = vector(&g_journal__->tokens, V_POPAT, index, NULL);
		g_journal__->counter[token->type]--;
		token_destroy(token);
		return (TRUE);
	}
	return (FALSE);
}

t_bool	journal_at_index_is_type(size_t index, e_token_type type)
{
	t_token				*token;

	token = journal_get(index);
	return (token && token->type == type);
}

size_t	journal_size(void)
{
	if (!g_journal__)
		return (0);
	else
		return (*(size_t *)vector(&g_journal__->tokens, V_SIZE, 0, 0));
}
