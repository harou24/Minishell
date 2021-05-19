#include "key_listener.h"

t_bool	is_key_arrow_up(const char *key)
{
	return (key[0] == ESCAPE_CHAR
		&& key[1] == BRACKET_LEFT
		&& key[2] == CHARACTER_A);
}

t_bool	is_key_arrow_down(const char *key)
{
	return (key[0] == ESCAPE_CHAR
		&& key[1] == BRACKET_LEFT
		&& key[2] == CHARACTER_B);
}

t_bool	is_key_arrow_right(const char *key)
{
	return (key[0] == ESCAPE_CHAR
		&& key[1] == BRACKET_LEFT
		&& key[2] == CHARACTER_C);
}
