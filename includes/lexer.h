#ifndef LEXER_H
# define LEXER_H

# include <stddef.h>
# include <stdlib.h>
# include "libft.h"
# include "hashmap.h"
# include "journal.h"

# ifndef __VECTOR_TYPEDEF
#  define __VECTOR_TYPEDEF
typedef void	*t_vector;
# endif

typedef struct s_lex
{
	char		*input;
	size_t		input_len;
	size_t		index;
	t_journal	*journal;
}				t_lex;

t_journal	*lex(const char *str);

t_token		*lex_get_next_token(void);
t_journal	*lex_build_journal(char *str);

void		lex_clear(void);
t_lex		*lex_create(void);
t_lex		*lex_destroy(t_lex **lex);

#endif
