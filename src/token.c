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

const char	*token_dump_type(e_token_type type)
{
	switch (type)
	{
		case WORD:
			return ("WORD");
		case STRING:
			return ("STRING");
		case VARIABLE:
			return ("VARIABLE");
		case SPACE:
			return ("SPACE");
		case PIPE:
			return ("PIPE");
		case NEWLINE:
			return ("NEWLINE");
		case SEMICOLON:
			return ("SEMICOLON");
		case OP_READ:
			return ("OP_READ");
		case OP_APPEND:
			return ("OP_APPEND");
		case OP_WRITE:
			return ("OP_WRITE");
		case NO_TYPE:
			return ("NO_TYPE");
		default:
			return ("UNKNOWN");
	}
}
