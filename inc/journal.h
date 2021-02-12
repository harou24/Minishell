#ifndef JOURNAL_H
# define JOURNAL_H

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"
#include "vector.h"

#ifndef __VECTOR_TYPEDEF
# define __VECTOR_TYPEDEF
typedef void * t_vector;
#endif

#include "token.h"

typedef int				t_journal_storetype;

typedef struct			s_journal
{
	t_vector			tokens;
	t_journal_storetype	*counter;
}						t_journal;

void					*journal_add(t_token *token);
void					*journal_get(size_t index);
size_t					journal_size();
t_bool					journal_has_token(t_token *token);
t_bool					*journal_has_tokentype(const e_token_type type);
t_token					*journal_find_first_of_tokentype(const e_token_type type);
t_token					*journal_find_last_of_tokentype(const e_token_type type);

/* some ..._for functions not written yet */

t_journal				*journal_create(size_t size);
t_journal				*journal_create_for(size_t size);
t_journal				*journal_destroy();
t_journal				*journal_destroy_for(t_journal *journal);

#endif
