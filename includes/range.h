/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   range.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:10:29 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:10:30 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANGE_H
# define RANGE_H

# include <stddef.h>
# include "libft.h"

typedef struct s_range
{
	size_t			begin;
	union {
		size_t			end;
		size_t			len;
	};
}					t_range;

t_range				range(size_t begin, size_t end);
t_bool				in_range(t_range range, size_t index);
int					range_len(t_range r);
int					range_cmp(t_range a, t_range b);
char				*range_dump(t_range r);

#endif
