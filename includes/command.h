#ifndef COMMAND_H
# define COMMAND_H

#include "argv.h"

typedef struct	s_command
{
		char	*path;
		t_argv	*argv;
		int		fd_in;
		int		fd_out;
}		t_command;

t_command	*command_create(char *path, t_argv *argv);
t_command	*command_destroy(t_command **_command);

void		command_set_fds(t_command *cmd, int fd_in, int fd_out);

void		command_pretty_dump(t_command *cmd, int indent);
#endif
