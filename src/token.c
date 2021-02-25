#include "token.h"

int			token_cmp(const t_token *a, const t_token *b)
{
	return ((a->type == b->type) ? 0 : 1);
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
	if (token)
	{
		free(token->string);
		free(token);
	}
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
		case LITERAL:
			return ("LITERAL");
		case ASSIGNMENT:
			return ("ASSIGNMENT");
		case ESCAPE:
			return ("ESCAPE");
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
