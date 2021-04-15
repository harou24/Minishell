/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bash_pattern.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:08:55 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:08:56 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASH_PATTERN_H
# define BASH_PATTERN_H

# include "range.h"
# include "journal.h"
# include "token.h"

# ifndef __VECTOR_TYPEDEF
#  define __VECTOR_TYPEDEF
typedef void *t_vector;
# endif

# define B_PAT_MAXLEN 128

typedef enum e_bash_pattern_type
{
	P_COMMAND,
	P_ASSIGNMENT,
	P_NO_TYPE
}	t_bash_pattern_type;

typedef struct s_bash_pattern
{
	const t_bash_pattern_type	pattern_type;
	const size_t				fixed_types_len;
	const t_token_type_e		fixed_types[B_PAT_MAXLEN];
	const size_t				fuzzy_types_len;
	const t_token_type_e		fuzzy_types[B_PAT_MAXLEN];
}	t_bash_pattern;

t_bash_pattern_type				bash_match_pattern(t_range range);

/* internal */
t_bool							match_token_to_type(t_token *token,
									const t_token_type_e type);
char							*pattern_dump_type(t_bash_pattern_type type);

#endif
