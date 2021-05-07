#ifndef CURSOR_H
# define CURSOR_H

typedef struct s_cursor
{
	int row;
	int col;
}			t_cursor;

t_cursor	*cursor_create(void);
void		cursor_set_pos(t_cursor *curs);
void		cursor_destroy(t_cursor *cursor);

#endif
