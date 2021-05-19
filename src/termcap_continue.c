#include <termcap.h>
#include "env_singleton.h"
#include <unistd.h>
#include "libft.h"

int	termcap_putchar(int c)
{
	return (write(STDOUT, &c, 1));
}

t_bool	termcap_init(t_termcap *termcap)
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
		return (FALSE);
	tgetent(NULL, term_name);
	return (TRUE);
}

void	termcap_deinit(t_termcap *termcap)
{
	tcgetattr(STDIN, &termcap->term);
	termcap->term.c_lflag |= (ECHO | ICANON | ISIG);
	tcsetattr(STDIN, TCSANOW, &termcap->term);
}

t_bool	termcap_execute(const char *cap)
{
	const char	*code = tgetstr((char *)cap, NULL);

	if (!code)
		return (FALSE);
	if (!tputs(code, STDOUT, termcap_putchar))
		return (FALSE);
	return (TRUE);
}
