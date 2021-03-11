#ifndef FILESYSTEM_H
# define FILESYSTEM_H

#include "libft.h"

#undef PATH_MAX
#define PATH_MAX	4096

t_bool	file_exists(const char *filename);
t_bool	file_is_executable(const char *filename);

t_bool	directory_exists(const char *dir);
char	*directory_get_current_dir(void);

int		directory_change_dir(const char *path);

#endif
