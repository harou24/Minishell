#include <assert.h>
#include "journal.h"

t_journal	*g_journal__;

void	journal_clear_input_str(void)
{
	free(g_journal__->str);
	g_journal__->str = NULL;
}

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

void	journal_reset_counters(void)
{
	size_t	i;

	i = 0;
	while (i < TOKEN_TYPE_SIZE)
	{
		g_journal__->counter[i] = 0;
		i++;
	}
	journal_creeper_reset();
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

t_journal	*journal_destroy(t_journal **journal)
{
	if (!g_journal__)
		return (NULL);
	journal_clear();
	journal_clear_input_str();
	vector(&g_journal__->tokens, V_DESTROY, FALSE, 0);
	free(g_journal__->counter);
	free(g_journal__);
	if (journal)
		*journal = NULL;
	return ((g_journal__ = NULL));
}
