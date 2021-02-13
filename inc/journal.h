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
	size_t				index;
}						t_journal;

t_token					*journal_add(t_token *token);
t_token					*journal_get(size_t index);

size_t					journal_size();

t_bool					journal_has_token(const t_token *token);
t_bool					journal_has_tokentype(const e_token_type type);

t_token                 *journal_find_first_token(const t_token *token);
t_token                 *journal_find_last_token(const t_token *token);
t_token					*journal_find_first_type(const e_token_type type);
t_token					*journal_find_last_type(const e_token_type type);

t_token					*journal_next();
void					journal_reset();

size_t					journal_get_index();
void					journal_set_index(size_t index);


/* some ..._for functions not written yet */

t_journal				*journal_create(size_t size);
t_journal				*journal_create_for(size_t size);
t_journal				*journal_destroy();
t_journal				*journal_destroy_for(t_journal *journal);

#endif
