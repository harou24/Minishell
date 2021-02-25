#include <assert.h>
#include <stdlib.h>
#include "libft.h"
#include "command.h"

t_command	*command_create(const char *path, const char **argv, int argc)
{
	t_command *cmd;

	cmd = ft_calloc(sizeof(t_command), 1);
	if (cmd)
	{
		cmd->path = (char *)path;
		cmd->argv = (char **)argv;
		cmd->argc = argc;
		cmd->fd_in = STDIN;
		cmd->fd_out = STDOUT;
	}
	return (cmd);
}

t_command	*command_destroy(t_command *cmd)
{
	if (cmd)
	{
		free(cmd->path);
		ft_array_destroy((void **)cmd->argv, cmd->argc);
	}
	return (NULL);
}

void		command_set_fds(t_command *cmd, int fd_in, int fd_out)
{
	assert(cmd);
	cmd->fd_in = fd_in;
	cmd->fd_out = fd_out;
}
