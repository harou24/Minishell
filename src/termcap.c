#include "termcap.h"
#include "libft.h"
#include "env_singleton.h"
#include <stdlib.h>
#include <unistd.h>

#define DELETE 127
#define NEW_LINE 12
#define	ESCAPE 27
#define	LEFT_BRACKET 91

int	ft_putchar(int c)
{
	return(write(STDOUT, &c, 1));
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

static	t_bool	_is_key_arrow_up(char *buffer)
{
	return (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 65);
}

char	*termcap_add_char_into(t_termcap *term, char *buffer, char *tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (term->line && term->line[i])
	{
		if (term->cursor == j)
			tmp[j++] = buffer[0];
		tmp[j++] = term->line[i++];
	}
	if (j == term->cursor)
		tmp[j++] = buffer[0];
	tmp[j] = '\0';
	return (tmp);
}

void	termcap_add_char(t_termcap *term, char *buffer)
{
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * ft_strlen(term->line + 2));
	if (!tmp)
		return ;
	if (term->line)
		tmp = termcap_add_char_into(term, buffer, tmp);
	else if (!term->line)
	{
		tmp[0] = buffer[0];
		tmp[1] = '\0';
	}
	free(term->line);
	term->line = tmp;
	term->cursor++;
}

void	termcap_delete_char(t_termcap *term, int offset)
{
	int	i;

	if (term->cursor > 0)
	{
		i = term_cursor - offset;
		while (term->line && term->line[i])
		{
			term->line[i] = term_line[i + 1];
			i++;
		}
		term->cursor--;
	}
}

void	termcap_move_left(t_termcap *term)
{
	if (term->cursor > 0)
		term_cursor--;
}

void	termcap_move_right(t_termcap *term)
{
	if (term->cursor  < ft_strlen(term->line))
		term->cursor++;
}

void	termcap_move_up(t_termcap *term)
{

}

void	termcap_move_down(t_termcap *term)
{

}

void	termcap_handle_key(t_termcap *term, char *buffer)
{
	char	*tc_str;
	
	if (ft_strlen(buffer) == 1 && ft_isprint(buffer[0]))
		termcap_add_char(term, buffer);
	else if (buffer[0] == NEW_LINE)
		term->enter = 0;
	else if (buffer[0] == DELETE)
		termcap_delete_char(term, 1);
	else if (buffer[0] == 27 && buffer[1] == 91
			&& buffer[2] == 51 && buffer[3] == 126)
		termcap_delete_char(term, 0);
	else if (buffer[0] == NEW_LINE)
	{
		tputs(tgetstr("cl", NULL), 1, ft_putchar);
	}
	else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 68)
		termcap_move_left(term);
	else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 67)
		termcap_move_right(term);
	else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 65)
		termcap_move_up(term);
	else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 66)
		termcap_move_down(term);
}

void	termcap_print_cursor()
{
	if (term->cursor == ft_strlen())
}
