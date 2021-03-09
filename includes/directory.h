#ifndef DIRECTORY_H
# define DIRECTORY_H

char	*directory_get_current_dir(void);
int	directory_change_dir(const char *path);
int	directory_exist(const char *dir);

#endif
