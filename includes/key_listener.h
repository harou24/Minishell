#ifndef KEY_LISTENER_H
# define KEY_LISTENER_H

# include "libft.h"

t_bool  is_key_backspace(const char *key);
t_bool  is_key_arrow_up(const char *key);
t_bool  is_key_arrow_down(const char *key);
t_bool  is_key_arrow_left(const char *key);
t_bool  is_key_arrow_right(const char *key);
t_bool  is_key_new_line(const char *key);
t_bool  is_key_printable(const char *key);

#endif
