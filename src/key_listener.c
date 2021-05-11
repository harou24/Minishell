#include "key_listener.h"

t_bool  is_key_arrow_up(const char *key)
{
    return (key[0] == ESCAPE_CHAR  && key[1] == BRACKET_LEFT && key[2] == CHARACTER_A);
}

t_bool  is_key_arrow_down(const char *key)
{
    return (key[0] == ESCAPE_CHAR && key[1] == BRACKET_LEFT && key[2] == CHARACTER_B);
}

t_bool  is_key_arrow_right(const char *key)
{
    return (key[0] == ESCAPE_CHAR  && key[1] == BRACKET_LEFT && key[2] == CHARACTER_C);
}

t_bool  is_key_arrow_left(const char *key)
{
    return (key[0] == ESCAPE_CHAR && key[1] == BRACKET_LEFT && key[2] == CHARACTER_D);
}

t_bool  is_key_new_line(const char *key)
{
    return (key[0] == NEW_LINE);
}

t_bool  is_key_printable(const char *key)
{
    if (ft_isprint(key[0]))
        return (TRUE);
    return (FALSE);
}

t_bool  is_key_backspace(const char *key)
{
    return (key[0] == DELETE);
}
