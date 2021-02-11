#ifndef LEXER_H
# define LEXER_H

#ifndef __VECTOR_TYPEDEF
# define __VECTOR_TYPEDEF
typedef void * t_vector;
#endif

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"
#include "token.h"

typedef struct	s_lexer
{
	t_vector	tokens;
}				t_lexer;

static const size_t g_lexer_default_size = 128;

t_bool		lexer(t_lexer *lex, const char *str);

t_lexer     *lexer_create();
t_lexer     *lexer_destroy(t_lexer *lex);

#endif
