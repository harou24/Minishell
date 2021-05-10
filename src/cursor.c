#include "cursor.h"
#include "termcap.h"
#include <stdlib.h>

t_cursor    *cursor_create(void)
{
    t_cursor    *cursor;

    cursor = malloc(sizeof(t_cursor));
    if (!cursor)
        return (NULL);
    cursor->pos = 0;
    cursor->start = 0;
    cursor->end = 0;
    return (cursor);
}

t_bool    cursor_move_left(t_cursor *cursor)
{
    if (cursor->pos > cursor->start)
    {
        termcap_move_left();
        cursor->pos--;
        return (TRUE);
    }
    return(FALSE);
}

t_bool    cursor_move_right(t_cursor *cursor)
{
    if (cursor->pos + 1 < cursor->end + 1)
    {
        termcap_move_right();
        cursor->pos++;
        return (TRUE);
    }
    return (FALSE);
}

void    cursor_reset(t_cursor *cursor)
{
    cursor->pos = 0;
    cursor->start = 0;
    cursor->end = 0;
}

void    cursor_set_start(t_cursor *cursor, int pos)
{
    cursor->start = pos;
}

void    cursor_set_end(t_cursor *cursor, int pos)
{
    cursor->end = pos;
}

void    cursor_destroy(t_cursor *cursor)
{
    free(cursor);
}
