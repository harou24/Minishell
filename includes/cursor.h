#ifndef CURSOR_H
# define CURSOR_H

# include "libft.h"

typedef struct s_cursor
{
    int     pos;
    int     start;
    int     end;
}           t_cursor;

t_cursor    *cursor_create(void);
t_bool  cursor_move_left(t_cursor *cursor);
t_bool  cursor_move_right(t_cursor *cursor);
void    cursor_reset(t_cursor *cursor);
void    cursor_set_start(t_cursor *cursor, int  pos);
void    cursor_set_end(t_cursor *cursor, int pos);
t_bool  cursor_increase_pos(t_cursor *cursor);
t_bool  cursor_decrease_pos(t_cursor *cursor);
void    cursor_destroy(t_cursor *cursor);

#endif
