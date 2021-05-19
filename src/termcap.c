#include <termcap.h>
#include "env_singleton.h"
#include <unistd.h>
#include "libft.h"

t_bool	termcap_insert_char(char c)
{
	termcap_execute(SAVE_CURSOR);
	termcap_execute(INSERT_MODE);
	termcap_execute(INSERT_CHARACTER);
	termcap_putchar(c);
	termcap_execute(END_INSERT_MODE);
	termcap_execute(RESTORE_CURSOR);
	termcap_execute(MOVE_CURSOR_ONE_RIGHT);
	return (TRUE);
}

void	termcap_move_left(void)
{
	termcap_execute(MOVE_CURSOR_LEFT);
}

void	termcap_move_right(void)
{
	char	*code;

	code = tgetstr(MOVE_CURSOR_ONE_RIGHT, NULL);
	tputs(code, STDOUT, termcap_putchar);
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
