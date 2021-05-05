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

t_termcap	*termcap_create(void);
int	termcap_init(t_termcap *termcap);
void	termcap_destroy(t_termcap *termcap);
int	ft_putchar(int c);
#endif
