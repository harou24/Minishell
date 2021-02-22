#include <assert.h>
#include "journal.h"

# define V_DEF_SIZE	128

static t_journal *g_journal__;

t_journal        *journal_create()
{
	if (g_journal__)
		return (g_journal__);
	g_journal__ = ft_calloc(sizeof(t_journal), 1);
	if (g_journal__)
	{
		g_journal__->counter = ft_calloc(sizeof(t_journal_storetype), TOKEN_TYPE_SIZE);
		if (!g_journal__->counter
			|| !vector(&g_journal__->tokens, V_CREATE, V_DEF_SIZE, NULL))
			return (journal_destroy(&g_journal__));
	}
	return (g_journal__);
}

void			journal_set_input_str(char *str)
{
	journal_clear_input_str();
	g_journal__->str = ft_strdup(str);
}

char			*journal_get_input_str()
{
	return (g_journal__->str);
}

void			journal_clear_input_str()
{
	free(g_journal__->str);
	g_journal__->str = NULL;
}

void			journal_clear()
{
	/* this de-allocs all token elements in vector, which could be costly #40 */
	if (g_journal__)
	{
		while (journal_size() > 0)
		{
			token_destroy(vector(&g_journal__->tokens, V_PEEKBACK, 0, 0));
			vector(&g_journal__->tokens, V_POPBACK, 0, 0);
		}
		assert(journal_size() == 0);
		journal_reset_counters();
	}
}

void			journal_reset_counters()
{
	size_t i;

	i = 0;
	while(i < TOKEN_TYPE_SIZE)
	{
		g_journal__->counter[i] = 0;
		i++;
	}
	journal_creeper_reset();
}

void			journal_rebuild_tokens()
{
	const size_t	count = journal_size();
	size_t			i;
	t_token			*token;

	journal_reset_counters();
	i = 0;
	while (i < count)
	{
		token = vector(&g_journal__->tokens, V_PEEKAT, i, 0);
		token->index = i;
		(g_journal__->counter)[token->type]++;
		i++;
	}
}

t_journal        *journal_destroy(t_journal **journal)
{
	if (!g_journal__)
		return (NULL);
	while (journal_size() > 0)
	{
		token_destroy(vector(&g_journal__->tokens, V_PEEKBACK, 0, 0));
		vector(&g_journal__->tokens, V_POPBACK, 0, 0);
	}
	journal_clear_input_str();
	vector(&g_journal__->tokens, V_DESTROY, FALSE, 0);
	free(g_journal__->counter);
	free(g_journal__);
	if (journal)
		*journal = NULL;
	return ((g_journal__ = NULL));
}

t_token					*journal_push(t_token *token)
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

char					*journal_dump_tokens()
{
	char		*buf;
	const int	buflen = 1024;
	t_token		*token;
	size_t		i;

	i = 0;
	buf = ft_calloc(sizeof(char), buflen);
	while (i < journal_size())
	{
		token = vector(&g_journal__->tokens, V_PEEKAT, i, 0);
		ft_strlcat(buf, token_dump_type(token->type), buflen);
		if (token->string)
		{
			ft_strlcat(buf, "{", buflen);
			ft_strlcat(buf, token->string, buflen);
			ft_strlcat(buf, "}", buflen);
		}
		ft_strlcat(buf, " ", buflen);
		i++;
	}
	return (buf);
}

char					*journal_reconstruct_string()
{
	char		*buf;
	char		*str;
	const int	buflen = 1024;
	t_token		*token;
	size_t		i;

	i = 0;
	buf = ft_calloc(sizeof(char), buflen);
	while (i < journal_size())
	{
		token = vector(&g_journal__->tokens, V_PEEKAT, i, 0);
		str = journal_get_string_for_token(token);
		ft_strlcat(buf, str, buflen);
		free(str);
		i++;
	}
	return (buf);
}

int						journal_has_token(const t_token *token)
{
	return (journal_has_tokentype(token->type));
}

int						journal_has_tokentype(const e_token_type type)
{
	return (g_journal__->counter[type]);
}

t_token					*journal_find_nth_token(const t_token *token, int n)
{
	return (journal_find_nth_type(token->type, n));
}

t_token					*journal_find_nth_type(const e_token_type type, int n)
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

t_token					*journal_find_first_token(const t_token *token)
{
	return (journal_find_first_type(token->type));
}

t_token					*journal_find_last_token(const t_token *token)
{
	return (journal_find_last_type(token->type));
}

t_token					*journal_find_first_type(const e_token_type type)
{
	return (journal_find_nth_type(type, 0));
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
			return (cur_token);
		index--;
	}
	return (NULL);
}

t_token					*journal_creeper_next()
{
	if (g_journal__->index >= journal_size())
		return (NULL);
	return (journal_get(g_journal__->index++));
}

void					journal_creeper_reset()
{
	journal_creeper_set_index(0);
}

size_t					journal_creeper_get_index()
{
	return(g_journal__->index);
}

void					journal_creeper_set_index(size_t index)
{
	g_journal__->index = index;
}

t_vector				journal_get_token_vector()
{
	return (g_journal__->tokens);
}

void                    journal_build_linked_list()
{
	const size_t		size = journal_size();
	ssize_t				index;
	t_token				*cur_token;
	t_token				*last_token;

	if (size == 0)
		return ;
	index = size - 1;
	while (index >= 0)
	{
		cur_token = journal_get(index);
		if ((size_t)index < size - 1)
		{
			cur_token->next = last_token;
			last_token = cur_token;
		}
		else
		{
			/* only for last token */
			cur_token->next = NULL;
			last_token = cur_token;
		}
		cur_token->index = index;
		index--;
	}
	return ;
}

char					*journal_get_string_for_token(t_token *token)
{
	if (token->string)
		return (ft_strdup(token->string));
	else
		return (ft_strsub(g_journal__->str, token->range.begin, 1 + token->range.end - token->range.begin));
}
