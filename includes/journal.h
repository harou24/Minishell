#ifndef JOURNAL_H
# define JOURNAL_H

# include <stddef.h>
# include <stdlib.h>
# include "libft.h"
# include "vector.h"

# include "token.h"

# ifndef __VECTOR_TYPEDEF
#  define __VECTOR_TYPEDEF
typedef void	*t_vector;
# endif

typedef int	t_journal_storetype;

typedef struct s_journal
{
	char				*str;
	t_vector			tokens;
	t_journal_storetype	*counter;
	size_t				index;
}						t_journal;

/*
** R U A FUNCTION ?
*/

t_journal				*journal_create(void);
t_journal				*journal_destroy(t_journal **journal);

void					journal_set_input_str(char *str);
char					*journal_get_input_str(void);
void					journal_clear_input_str(void);

void					journal_clear(void);
void					journal_reset_counters(void);
void					journal_rebuild_tokens(void);

t_token					*journal_push(t_token *token);
t_token					*journal_get(size_t index);
t_bool					journal_remove(size_t index);

t_bool					journal_at_index_is_type(size_t index,
							e_token_type type);

size_t					journal_size(void);

char					*journal_dump_tokens(void);
char					*journal_dump_tokens_for_range(t_range r);

int						journal_has_token(const t_token *token);
int						journal_has_tokentype(const e_token_type type);

t_token					*journal_find_nth_token(const t_token *token, int n);
t_token					*journal_find_nth_type(const e_token_type type, int n);

t_token					*journal_find_first_token(const t_token *token);
t_token					*journal_find_last_token(const t_token *token);
t_token					*journal_find_first_type(const e_token_type type);
t_token					*journal_find_last_type(const e_token_type type);

void					journal_remove_tokens_with_type(e_token_type type);

t_token					*journal_creeper_next(void);
void					journal_creeper_reset(void);

size_t					journal_creeper_get_index(void);
void					journal_creeper_set_index(size_t index);

t_vector				journal_get_token_vector(void);

void					journal_build_linked_list(void);

char					*journal_get_string_for_token(t_token *token);
char					*journal_get_string_for_index(size_t index);
char					*journal_reconstruct_string(void);

#endif
