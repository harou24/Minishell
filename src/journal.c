#include "journal.h"

# define V_DEF_SIZE	(TOKEN_TYPE_INDEX + 1)

t_journal        *journal_create(size_t size)
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

t_journal        *journal_destroy(t_journal *journal)
{
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
