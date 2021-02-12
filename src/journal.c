#include "journal.h"

# define V_DEF_SIZE	(TOKEN_TYPE_INDEX + 1)

static t_journal *g_journal__;

t_journal        *journal_create(size_t size)
{
	if (g_journal__)
		return (g_journal__);
	else
		return ((g_journal__ = journal_create_for(size)));
}

t_journal        *journal_create_for(size_t size)
{
	t_journal	*journal;

	journal = ft_calloc(sizeof(t_journal), 1);
	if (journal)
	{
		journal->counter = ft_calloc(sizeof(t_journal_storetype), size);
		if (!journal->counter
			|| !vector(&journal->tokens, V_CREATE, V_DEF_SIZE, NULL))
			return (journal_destroy(journal));
	}
	return (journal);
}

t_journal        *journal_destroy()
{
	journal_destroy_for(g_journal__);
	return ((g_journal__ = NULL));
}

t_journal        *journal_destroy_for(t_journal *journal)
{
	if (!journal)
		return (NULL);
	while (*(size_t *)vector(&journal->tokens, V_SIZE, 0, 0) > 0)
	{
		token_destroy(vector(&journal->tokens, V_PEEKBACK, 0, 0));
		vector(&journal->tokens, V_POPBACK, 0, 0);
	}
	vector(&journal->tokens, V_DESTROY, FALSE, 0);
	free(journal->counter);
	free(journal);
	return (NULL);
}

void					*journal_add(t_token *token)
{

}

void					*journal_get(size_t index)
{

}

size_t					journal_size()
{

}

t_bool					journal_has_token(t_token *token)
{

}

t_bool					*journal_has_tokentype(const e_token_type type)
{

}

t_token					*journal_find_first_of_tokentype(const e_token_type type)
{

}

t_token					*journal_find_last_of_tokentype(const e_token_type type)
{

}

