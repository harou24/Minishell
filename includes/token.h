/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:10:37 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:10:39 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stddef.h>
# include <stdlib.h>
# include "libft.h"
# include "range.h"

typedef enum e_token_type_e
{
	WORD,
	SYM,
	STRING,
	LITERAL,
	ASSIGNMENT,
	ESCAPE,
	VARIABLE,
	SPACE,
	PIPE,
	NEWLINE,
	SEMICOLON,
	LEFTSHIFT,
	RIGHTSHIFT,
	DOUBLERIGHTSHIFT,
	NULLBYTE,
	NO_TYPE,
	TOKEN_TYPE_SIZE
}	t_token_type_e;

struct	s_token;
typedef struct s_token
{
	t_token_type_e		type;
	t_range				range;
	char				*string;
	size_t				index;
	struct s_token		*next;
}					t_token;

int					token_cmp(const t_token *a, const t_token *b);

t_token				token(t_range range, t_token_type_e type);

t_token				*token_create(t_range range, t_token_type_e type);
t_token				*token_destroy(t_token *token);

const char			*token_dump_type(t_token_type_e type);

t_bool				token_is_variable(t_token *token);
t_bool				token_is_redirection(t_token *token);
t_bool				token_is_relation(t_token *token);
t_bool				token_is_alnum(t_token *token);
t_bool				token_is_space(t_token *token);
t_bool				token_is_assignment(t_token *token);
t_bool				token_is_escape(t_token *token);

#endif
