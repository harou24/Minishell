#ifndef TERMCAP_H
# define TERMCAP_H

# include <term.h>
# include "libft.h"

# define MOVE_CURSOR_LEFT "le"
# define MOVE_CURSOR_RIGHT "RI"
# define DELETE_CHAR "dc"
# define SAVE_CURSOR "sc"
# define INSERT_MODE "im"
# define INSERT_CHARACTER "ic"
# define END_INSERT_MODE "er"
# define RESTORE_CURSOR "rc"
# define MOVE_CURSOR_ONE_RIGHT "nd"

typedef struct s_termcap
{
	struct termios	term;
}			t_termcap;

int		termcap_putchar(int c);
t_bool	termcap_init(t_termcap *term);
t_bool	termcap_execute(const char *cap);
void	termcap_deinit(t_termcap *term);

t_bool	termcap_backspace(void);
t_bool	termcap_clean_line(void);
t_bool	termcap_arrow_down(void);
void	termcap_move_left(void);
void	termcap_move_right(void);
t_bool	termcap_insert_char(char c);
t_bool	termcap_is_key_arrow_up(char *buffer);
t_bool	termcap_is_key_arrow_left(char *buffer);
t_bool	termcap_is_key_arrow_right(char *buffer);
t_bool	termcap_is_key_arrow_down(char *buffer);
t_bool	termcap_is_key_new_line(char *buffer);
t_bool	termcap_is_key_printable(char *buffer);
t_bool	termcap_is_key_backspace(char *buffer);

#endif
