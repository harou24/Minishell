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

const char	*token_dump_type(e_token_type type)
{
	if (type == WORD)
		return ("WORD");
	if (type == STRING)
		return ("STRING");
	if (type == LITERAL)
		return ("LITERAL");
	if (type == ASSIGNMENT)
		return ("ASSIGNMENT");
	if (type == ESCAPE)
		return ("ESCAPE");
	if (type == VARIABLE)
		return ("VARIABLE");
	if (type == SPACE)
		return ("SPACE");
	if (type == PIPE)
		return ("PIPE");
	if (type == NEWLINE)
		return ("NEWLINE");
	if (type == SEMICOLON)
		return ("SEMICOLON");
	if (type == OP_READ)
		return ("OP_READ");
	if (type == OP_APPEND)
		return ("OP_APPEND");
	if (type == OP_WRITE)
		return ("OP_WRITE");
	if (type == NULLBYTE)
		return ("NULLBYTE");
	if (type == NO_TYPE)
		return ("NO_TYPE");
	return ("UNKNOWN");
}
