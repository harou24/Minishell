#include "range.h"
#include "ft_printf.h"

t_range             range(size_t begin, size_t end)
{
	t_range range;

	range.begin = begin;
	range.end = end;
	return (range);
}

int				range_cmp(t_range a, t_range b)
{
	return (!(a.begin == b.begin && a.end == b.end));
}

char			*range_dump(t_range r)
{
	char		*buf;
	const int	buflen = 1024;

	buf = ft_calloc(buflen, sizeof(char));
	ft_snprintf(buf, buflen, "{%i : %i}", r.begin, r.end);
	return (buf);
}
