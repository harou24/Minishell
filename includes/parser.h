#ifndef PARSER_H
# define PARSER_H

#include "journal.h"
#include "execscheme.h"

typedef struct		s_parser
{
	t_execscheme	*scheme;
}					t_parser;

t_execscheme		*parse();

t_bool				parse_expand_strings(e_token_type string_type);

t_parser			*parser_create();
t_parser			*parser_destroy();

void				parse_replace_tokens_with_token(t_vector tokens, t_token *first, t_token *last, t_token *token);

#endif
