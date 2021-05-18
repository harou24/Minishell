#ifndef KEY_LISTENER_H
# define KEY_LISTENER_H

# include "libft.h"

# define NEW_LINE       10
# define ESCAPE_CHAR    27
# define CHARACTER_A    65
# define CHARACTER_B    66
# define CHARACTER_C    67
# define CHARACTER_D    68
# define BRACKET_LEFT   91
# define DELETE         127
# define CNTRL_D        4
# define CNTRL_U        21

t_bool	is_key_backspace(const char *key);
t_bool	is_key_arrow_up(const char *key);
t_bool	is_key_arrow_down(const char *key);
t_bool	is_key_arrow_left(const char *key);
t_bool	is_key_arrow_right(const char *key);
t_bool	is_key_new_line(const char *key);
t_bool	is_key_printable(const char *key);

#endif
