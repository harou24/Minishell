#ifndef BASH_SYM_H
# define BASH_SYM_H

#include "token.h"

typedef struct					s_bash_sym
{
	const e_token_type			type;
	const int					match_style;
	const char					*key;
}								t_bash_sym;

e_token_type					bash_match(const char *str, size_t len);

#endif
