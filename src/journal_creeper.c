#include <assert.h>
#include "journal.h"

extern t_journal	*g_journal__;

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
