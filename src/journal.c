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

t_token					*journal_add(t_token *token)
{
	
	if (vector(&g_journal__->tokens, V_PUSHBACK, 0, token))
		return (token);
	else
		return (NULL);

}

t_token					*journal_get(size_t index)
{
	if (index >= journal_size())
		return (NULL);
	else
		return (vector(&g_journal__->tokens, V_PEEKAT, index, NULL));
}

size_t					journal_size()
{
	if (!g_journal__)
		return (0);
	else
		return (*(size_t *)vector(&g_journal__->tokens, V_SIZE, 0, 0));
}

t_bool					journal_has_token(const t_token *token)
{
	return (journal_find_first_token(token) != NULL);
}

t_bool					journal_has_tokentype(const e_token_type type)
{
	return (journal_find_first_type(type) != NULL);
}

t_token					*journal_find_first_token(const t_token *token)
{
	const size_t		size = journal_size();
	size_t				index;
	t_token				*cur_token;

	index = 0;
	while (index < size)
	{
		cur_token = journal_get(index);
		if (token_cmp(cur_token, token) == TRUE)
			break;
		index++;
	}
	if (index < size)
		return (cur_token);
	return (NULL);
}

t_token					*journal_find_last_token(const t_token *token)
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
		if (token_cmp(cur_token, token) == TRUE)
			break;
		index--;
	}
	if (index >= 0)
		return (cur_token);
	return (NULL);
}

t_token					*journal_find_first_type(const e_token_type type)
{
	const size_t		size = journal_size();
	size_t				index;
	t_token				*cur_token;

	index = 0;
	while (index < size)
	{
		cur_token = journal_get(index);
		if (cur_token->type == type)
			break;
		index++;
	}
	if (index < size)
		return (cur_token);
	return (NULL);
}

t_token					*journal_find_last_type(const e_token_type type)
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
			break;
		index--;
	}
	if (index >= 0)
		return (cur_token);
	return (NULL);

}

t_token					*journal_next()
{
	if (!g_journal__ || g_journal__->index >= journal_size())
		return (NULL);
	return (journal_get(g_journal__->index++));
}

void					journal_reset()
{
	if (g_journal__)
		journal_set_index(0);
}

size_t					journal_get_index()
{
	if (!g_journal__)
		return (0);
	else
		return(g_journal__->index);
}

void					journal_set_index(size_t index)
{
	if (g_journal__)
		g_journal__->index = index;
}
