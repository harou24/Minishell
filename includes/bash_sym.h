/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bash_sym.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:08:59 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:09:00 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASH_SYM_H
# define BASH_SYM_H

# include "token.h"

typedef struct s_bash_sym
{
	const t_token_type_e		type;
	const int					match_style;
	const char					*key;
}	t_bash_sym;

t_token_type_e					bash_match(const char *str, size_t len);

#endif
