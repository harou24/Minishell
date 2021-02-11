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

void					*journal_add_token(t_token *token);

t_journal				*journal_create(size_t size);
t_journal				*journal_destroy(t_journal *journal);

#endif
