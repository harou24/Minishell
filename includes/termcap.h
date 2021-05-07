#ifndef TERMCAP_H
# define TERMCAP_H

# include <term.h>

# define UP "\e[A"
# define DOWN "\e[B"
# define BACKSPACE "\177"

typedef struct		s_termcap
{
	char		*buffer;
	char		*line;
	int		cursor;
	int		enter;
	t_history	*current;
}				t_termcap;

int		termcap_init(t_termcap *term);
int		termcap_putchar(int c);

void		termcap_handle_key(t_termcap *term, char *buffer);
void		termcap_print_cursor(t_termcap *term);



#endif
