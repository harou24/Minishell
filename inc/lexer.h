#ifndef LEXER_H
# define LEXER_H

#include "token.h"

typedef struct	s_lexer
{
		t_token *tokens;
		size_t	size;
		size_t	count;
}		t_lexer;
#endif
