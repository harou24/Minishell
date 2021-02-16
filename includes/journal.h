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

/*
** R U A FUNCTION ?
*/

t_journal				*journal_create();
void					journal_clear();
t_journal				*journal_destroy(t_journal **journal);

t_token					*journal_push(t_token *token);
t_token					*journal_get(size_t index);

size_t					journal_size();

char					*journal_dump_tokens();

t_bool					journal_has_token(const t_token *token);
t_bool					journal_has_tokentype(const e_token_type type);

t_token                 *journal_find_first_token(const t_token *token);
t_token                 *journal_find_last_token(const t_token *token);
t_token					*journal_find_first_type(const e_token_type type);
t_token					*journal_find_last_type(const e_token_type type);

t_token					*journal_creeper_next();
void					journal_creeper_reset();

size_t					journal_creeper_get_index();
void					journal_creeper_set_index(size_t index);

#endif
