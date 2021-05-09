#include <termcap.h>
#include "env_singleton.h"
#include <unistd.h>
#include "libft.h"

# define MOVE_CURSOR_LEFT "le"
# define DELETE_CHAR "dc"

int	termcap_putchar(int c)
{
	return(write(STDOUT, &c, 1));
}

t_bool	termcap_execute(const char *cap)
{
	const char *code = tgetstr((char *)cap, NULL);
	if (!code)
		return (FALSE);
	if (!tputs(code, STDOUT, termcap_putchar))
		return (FALSE);
	return (TRUE);
}

void    termcap_move_left(void)
{
	termcap_execute(MOVE_CURSOR_LEFT);
}

t_bool	termcap_backspace(void)
{
    termcap_move_left();
	termcap_execute(DELETE_CHAR);
	return (TRUE);
}

t_bool	termcap_clean_line(void)
{
	termcap_execute("dl");
	tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, termcap_putchar);
	return (TRUE);
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

t_bool	termcap_is_key_arrow_up(char *buffer)
{
	return (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 65);
}

t_bool	termcap_is_key_arrow_down(char *buffer)
{
	return (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 66);
}

t_bool	termcap_is_key_arrow_left(char *buffer)
{
	return (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 68);
}

t_bool	termcap_is_key_arrow_right(char *buffer)
{
	return (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 67);
}

t_bool	termcap_is_key_new_line(char *buffer)
{
	return (buffer[0] == '\n');
}

t_bool	termcap_is_key_printable(char *buffer)
{
	if (ft_isprint(buffer[0]))
		return (TRUE);
	return (FALSE);
}

t_bool	termcap_is_key_backspace(char *buffer)
{
	return (buffer[0] == 127);
}
