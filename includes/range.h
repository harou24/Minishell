#ifndef RANGE_H
# define RANGE_H

#include <stddef.h>

typedef struct		s_range
{
	size_t			begin;
	size_t			end;
}					t_range;

t_range				range(size_t begin, size_t end);
int					range_cmp(t_range a, t_range b);
char				*range_dump(t_range r);

#endif
