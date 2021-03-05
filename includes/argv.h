#ifndef ARGV_H
# define ARGV_H

#include "libft.h"

typedef struct		s_argv
{
	char			**argv;
	int				argc;
	int				size;
}					t_argv;

char				*argv_get(t_argv *argv, int index);
t_bool				argv_push(t_argv *argv, char *arg);

t_argv				*argv_create(int size);
t_argv				*argv_destroy(t_argv **argv);

void				argv_pretty_dump(t_argv *argv, int indent);

#endif
