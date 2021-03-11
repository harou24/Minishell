#ifndef PATH_H
# define PATH_H

#include "libft.h"

t_bool	is_in_path(const char *execname, const char *path);

char	*get_full_path(const char *execname, const char *path);

#endif
