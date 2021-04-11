#ifndef ENVIRON_H
# define ENVIRON_H

# include "libft.h"

t_bool		environ_init(char **environ);
t_bool		environ_deinit(void);

char		**environ_get(void);
t_bool		environ_set(size_t index, char *line);
t_bool		environ_add(char *line);
size_t		environ_size(void);
void		environ_remove(size_t index);

#endif
