#include "token.h"

t_range             range(size_t begin, size_t end)
{
	t_range range;

	range.begin = begin;
	range.end = end;
	return (range);
}

/* is token always the smallest token ? */

/*
t_bool		token_find_in_str(const char *str, size_t begin, size_t len)
{
	
}
*/

int			token_cmp(const t_token *a, const t_token *b)
{
	return ((a->type == b->type) ? 0 : 1);
	/* return (ft_memcmp(a, b, sizeof(t_token) == 0)); */
}

t_token		token(t_range range, e_token_type type)
{
	t_token token;

	token.range = range;
	token.type = type;
	return (token);
}

t_token		*token_create(t_range range, e_token_type type)
{
	t_token *token;

	token = ft_calloc(sizeof(t_token), 1);
	if (token)
	{
		token->range = range;
		token->type = type;
	}
	return (token);
}

t_token		*token_destroy(t_token *token)
{
	free(token);
	return (NULL);
}
