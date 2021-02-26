#ifndef COMMAND_H
# define COMMAND_H

typedef struct	s_command
{
		char	*path;
		char	**argv;
		int		argc;
		int		fd_in;
		int		fd_out;
}		t_command;

t_command	*command_create(const char *path, const char **argv, int argc);
t_command	*command_destroy(t_command **_command);

void		command_set_fds(t_command *cmd, int fd_in, int fd_out);

#endif
