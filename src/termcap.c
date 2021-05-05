#include "termcap.h"
#include "libft.h"
#include "env_singleton.h"
#include <stdlib.h>
#include <unistd.h>

int	ft_putchar(int c)
{
	return(write(STDOUT, &c, 1));
}

t_termcap	*termcap_create()
{
	t_termcap	*termcap;

	termcap = (t_termcap *)malloc(sizeof(t_termcap));
	return (termcap);
}

int	termcap_init(t_termcap *termcap)
{
	char	*term_name;

	tcgetattr(STDIN, &termcap->term);
	termcap->term.c_lflag &= ~ICANON;
	termcap->term.c_lflag &= ~ECHO;
	termcap->term.c_cc[VMIN] = 1;
	termcap->term.c_cc[VTIME] = 0;
	tcsetattr(STDIN, TCSANOW, &termcap->term);
	term_name = env_get_s("TERM");
	if (!term_name)
		return (0);
	tgetent(NULL, term_name);
	return (1);
}

void	termcap_destroy(t_termcap *termcap)
{
	free(termcap);
}
