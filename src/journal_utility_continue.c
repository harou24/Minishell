#include <assert.h>
#include "journal.h"

extern t_journal	*g_journal__;

void	journal_clear(void)
{
	if (g_journal__)
	{
		while (journal_size() > 0)
			token_destroy(vector(&g_journal__->tokens, V_POPBACK, 0, 0));
		assert(journal_size() == 0);
		journal_reset_counters();
	}
}

void	journal_clear_input_str(void)
{
	free(g_journal__->str);
	g_journal__->str = NULL;
}

void	journal_remove_tokens_with_type(t_token_type_e type)
{
	t_token				*token;

	while (journal_has_tokentype(type))
	{
		token = journal_find_last_type(type);
		journal_remove(token->index);
	}
	journal_rebuild_tokens();
}
