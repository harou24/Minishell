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
#endif
