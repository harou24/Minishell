#ifndef ENVIRON_H
# define ENVIRON_H

t_bool		environ_init(char **environ);
t_bool		environ_deinit();

char		**environ_get();
t_bool		environ_set(size_t index, char *line);
t_bool		environ_add(char *line);
void		environ_remove(size_t index);

#endif
