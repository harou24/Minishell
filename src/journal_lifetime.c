#include <assert.h>
#include "journal.h"

#define V_DEF_SIZE 128

t_journal	*g_journal__;

t_journal	*journal_create(void)
{
	if (g_journal__)
		return (g_journal__);
	g_journal__ = ft_calloc(sizeof(t_journal), 1);
	if (g_journal__)
	{
		g_journal__->counter = ft_calloc(
				sizeof(t_journal_storetype), TOKEN_TYPE_SIZE);
		if (!g_journal__->counter
			|| !vector(&g_journal__->tokens, V_CREATE, V_DEF_SIZE, NULL))
			return (journal_destroy(&g_journal__));
	}
	return (g_journal__);
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
