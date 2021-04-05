#include <assert.h>
#include "journal.h"

extern t_journal	*g_journal__;

t_vector	journal_get_token_vector(void)
{
	return (g_journal__->tokens);
}

void	journal_build_linked_list(void)
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
			cur_token->next = NULL;
			last_token = cur_token;
		}
		cur_token->index = index;
		index--;
	}
	return ;
}

char	*journal_get_string_for_token(t_token *token)
{
	if (token->string)
		return (ft_strdup(token->string));
	else
		return (ft_strsub(g_journal__->str,
				token->range.begin, 1 + token->range.end - token->range.begin));
}

char	*journal_get_string_for_index(size_t index)
{
	t_token				*token;

	token = journal_get(index);
	assert(token);
	return (journal_get_string_for_token(token));
}

char	*journal_reconstruct_string(void)
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
