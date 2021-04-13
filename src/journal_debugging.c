#include <assert.h>
#include "journal.h"

extern t_journal	*g_journal__;

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

	if (r.end > journal_size())
		return (NULL);
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
