#ifndef PATH_H
# define PATH_H

# include "libft.h"

t_bool	path_contains(const char *path, const char *name);

char	*path_expand(const char *path, const char *name);

#endif
