#include "cursor.h"
#include "termcap.h"
#include <stdlib.h>

t_bool	cursor_decrease_pos(t_cursor *cursor)
{
	if (cursor->pos > 0)
	{
		cursor->pos--;
		return (TRUE);
	}
	return (FALSE);
}

t_bool	cursor_increase_pos(t_cursor *cursor)
{
	if (cursor->pos < cursor->end + 1)
	{
		cursor->pos++;
		return (TRUE);
	}
	return (FALSE);
}

void	cursor_set_start(t_cursor *cursor, int pos)
{
	cursor->start = pos;
}

void	cursor_set_end(t_cursor *cursor, int pos)
{
	cursor->end = pos;
}

void	cursor_destroy(t_cursor *cursor)
{
	free(cursor);
}
