#ifndef LEXER_H
# define LEXER_H

#ifndef __VECTOR_TYPEDEF
# define __VECTOR_TYPEDEF
typedef void * t_vector;
#endif

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"
#include "journal.h"

typedef struct	s_lex
{
	t_journal	*journal;
}				t_lex;

static const size_t g_lex_default_size = 128;

t_journal	*lex(const char *str);
t_journal	*lex_for(t_lex *lex, const char *str);

t_lex     	*lex_create();
t_lex     	*lex_create_for();

t_lex     	*lex_destroy();
t_lex     	*lex_destroy_for(t_lex *lex);

/* internal */


#endif
