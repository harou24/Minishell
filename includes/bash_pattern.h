#ifndef BASH_PATTERN_H
# define BASH_PATTERN_H

#include "range.h"
#include "journal.h"
#include "token.h"

#ifndef __VECTOR_TYPEDEF
# define __VECTOR_TYPEDEF
typedef void * t_vector;
#endif

#define B_PAT_MAXLEN			128

typedef enum					e_bash_pattern_type
{
	P_COMMAND,
	P_ASSIGNMENT,
	P_NO_TYPE
}								t_bash_pattern_type;

typedef struct					s_bash_pattern
{
	const t_bash_pattern_type	pattern_type;
	const size_t				fixed_types_len;
	const e_token_type			fixed_types[B_PAT_MAXLEN];
	const size_t				fuzzy_types_len;
	const e_token_type			fuzzy_types[B_PAT_MAXLEN];
}								t_bash_pattern;

t_bash_pattern_type				bash_match_pattern(t_range range);

/* sub functions */
t_bool                  match_token_to_type(t_token *token, const e_token_type type);
t_bool                  match_token_to_any_type(t_token *token, const e_token_type *types, size_t types_len);
t_bool                  match_fuzzy(t_range range, const e_token_type *fuzzy_types, size_t fuzzy_types_len);
t_bool                  match_fixed(t_range range, const e_token_type *fixed_types, size_t fixed_types_len);
t_bool                  is_bash_pattern(t_range r, const t_bash_pattern *pattern);

char					*pattern_dump_type(t_bash_pattern_type type);

#endif
