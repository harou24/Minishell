#ifndef COMMAND_H
# define COMMAND_H

#include "argv.h"

typedef struct	s_command
{
		char	*path;
		t_argv	*argv;
}				t_command;

t_command		*command_create(char *path, t_argv *argv);
t_command		*command_destroy(t_command **_command);

void			command_pretty_dump(t_command *cmd, int indent);
#endif
