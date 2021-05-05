#ifndef TERMCAP_H
# define TERMCAP_H

# include <term.h>

typedef struct		s_termcap
{
	struct termios	term;
	struct termios	save;
	char			*cm;
	char			*ce;
}					t_termcap;

int	termcap_init(t_termcap *termcap);

#endif
