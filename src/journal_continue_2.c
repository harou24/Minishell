#include <assert.h>
#include "journal.h"

extern t_journal	*g_journal__;

void	journal_remove_tokens_with_type(e_token_type type)
{
	t_token				*token;

	while (journal_has_tokentype(type))
	{
		token = journal_find_last_type(type);
		journal_remove(token->index);
	}
	journal_rebuild_tokens();
}

t_token	*journal_creeper_next(void)
{
	if (g_journal__->index >= journal_size())
		return (NULL);
	return (journal_get(g_journal__->index++));
}

void	journal_creeper_reset(void)
{
	journal_creeper_set_index(0);
}

size_t	journal_creeper_get_index(void)
{
	return (g_journal__->index);
}

void	journal_creeper_set_index(size_t index)
{
	g_journal__->index = index;
}
