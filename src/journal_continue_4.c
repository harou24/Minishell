#include <assert.h>
#include "journal.h"

extern t_journal	*g_journal__;

char	*journal_dump_tokens(void)
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

char	*journal_dump_tokens_for_range(t_range r)
{
	char		*buf;
	const int	buflen = 1024;
	t_token		*token;
	size_t		i;

	assert(r.end <= journal_size());
	i = r.begin;
	buf = ft_calloc(sizeof(char), buflen);
	while (i < r.end)
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

int	journal_has_token(const t_token *token)
{
	return (journal_has_tokentype(token->type));
}

int	journal_has_tokentype(const e_token_type type)
{
	return (g_journal__->counter[type]);
}

t_token	*journal_find_nth_token(const t_token *token, int n)
{
	return (journal_find_nth_type(token->type, n));
}
