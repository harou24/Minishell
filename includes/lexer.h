#ifndef LEXER_H
# define LEXER_H

#ifndef __VECTOR_TYPEDEF
# define __VECTOR_TYPEDEF
typedef void * t_vector;
#endif

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"
#include "hashmap.h"
#include "journal.h"

#ifndef __HASHMAP_TYPEDEF
# define __HASHMAP_TYPEDEF
typedef void * t_hashmap;
#endif

typedef struct	s_lex
{
	char		*input;
	size_t		input_len;
	size_t		index;
	t_journal	*journal;
	t_hashmap	key_store;
}				t_lex;

t_journal	*lex(const char *str);

t_token		*lex_get_next_token();
t_journal	*lex_build_journal();

void		lex_clear();
t_lex     	*lex_create();
t_lex     	*lex_destroy(t_lex **lex);

#endif
