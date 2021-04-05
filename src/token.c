#include "token.h"

int	token_cmp(const t_token *a, const t_token *b)
{
	if (a->type == b->type)
		return (0);
	else
		return (1);
}

t_token	token(t_range range, e_token_type type)
{
	t_token	token;

	token.range = range;
	token.type = type;
	return (token);
}

t_token	*token_create(t_range range, e_token_type type)
{
	t_token	*token;

	token = ft_calloc(sizeof(t_token), 1);
	if (token)
	{
		token->range = range;
		token->type = type;
	}
	return (token);
}

t_token	*token_destroy(t_token *token)
{
	if (token)
	{
		free(token->string);
		free(token);
	}
	return (NULL);
}
