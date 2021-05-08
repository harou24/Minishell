#ifndef TERMCAP_H
# define TERMCAP_H

# include <term.h>
# include "libft.h"

typedef struct s_termcap
{
	struct	termios term;
}			t_termcap;

int		termcap_putchar(int c);
int		termcap_init(t_termcap *term);
t_bool		termcap_execute(const char *cap);

t_bool	termcap_backspace(void);
t_bool	termcap_clean_line(void);
t_bool	termcap_arrow_down(void);

t_bool	termcap_is_key_arrow_up(char *buffer);
t_bool	termcap_is_key_arrow_down(char *buffer);
t_bool	termcap_is_key_new_line(char *buffer);
t_bool	termcap_is_key_printable(char *buffer);
t_bool	termcap_is_key_backspace(char *buffer);

#endif
