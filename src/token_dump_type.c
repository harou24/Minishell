#include "token.h"

static const char	*token_dump_type_continue(e_token_type type)
{
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

const char	*token_dump_type(e_token_type type)
{
	if (type == WORD)
		return ("WORD");
	if (type == SYM)
		return ("SYM");
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
	return (token_dump_type_continue(type));
}
