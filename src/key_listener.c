#include "key_listener.h"

t_bool	is_key_arrow_left(const char *key)
{
	return (key[0] == ESCAPE_CHAR
		&& key[1] == BRACKET_LEFT
		&& key[2] == CHARACTER_D);
}

t_bool	is_key_new_line(const char *key)
{
	return (key[0] == NEW_LINE);
}

t_bool	is_key_printable(const char *key)
{
	if (ft_isprint(key[0]))
		return (TRUE);
	return (FALSE);
}

t_bool	is_key_backspace(const char *key)
{
	return (key[0] == DELETE);
}
