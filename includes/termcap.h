#ifndef TERMCAP_H
# define TERMCAP_H

# include <term.h>

# define UP "\e[A"
# define DOWN "\e[B"
# define BACKSPACE "\177"

typedef struct		s_termcap
{
	struct termios	term;
}					t_termcap;

int		termcap_init(t_termcap *termcap);
int		termcap_putchar(int c);

void	termcap_arrow_up(void);
void	termcap_arrow_down(void);
void	termcap_backspace(void);

#endif
