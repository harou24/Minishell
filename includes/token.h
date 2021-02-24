#ifndef TOKEN_H
# define TOKEN_H

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"
#include "range.h"

typedef enum		s_token_type
{
					WORD,
					STRING,
					LITERAL,
					ESCAPE,
					VARIABLE,
					SPACE,
					PIPE,
					NEWLINE,
					SEMICOLON,
					OP_READ,
					OP_APPEND,
					OP_WRITE,
					NO_TYPE,
					TOKEN_TYPE_SIZE
}					e_token_type;

struct				s_token;
typedef struct		s_token
{
	e_token_type	type;
	t_range			range;
	char			*string;
	size_t			index;
	struct s_token	*next;
}					t_token;

/*
t_bool      token_find_in_str(const char *str, size_t begin, size_t len);
*/

int					token_cmp(const t_token *a, const t_token *b);

t_token				token(t_range range, e_token_type type);
t_token				*token_create(t_range range, e_token_type type);
t_token				*token_destroy(t_token *token);

const char			*token_dump_type(e_token_type type);

#endif
