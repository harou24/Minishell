#include "termcap.h"
#include "libft.h"

int	termcap_init(t_termcap *termcap)
{
	tcgetattr(STDIN, &termcap->term);
	termcap->term.c_lflag &= ~ICANON;
	termcap->term.c_lflag &= ~ECHO;
	termcap->term.c_cc[VMIN] = 1;
	termcap->term.c_cc[VTIME] = 0;
	tcsetattr(STDIN, TCSANOW, &termcap->term);
	tgetent(NULL, "xterm");
	termcap->cm = tgetstr("cm", NULL);
	termcap->ce = tgetstr("ce", NULL);
	return (1);
}
