#include <assert.h>
#include <stdlib.h>

#include "libft.h"

#include "command.h"

t_command	*command_create(char *path, t_argv *argv)
{
	t_command *cmd;

	cmd = ft_calloc(sizeof(t_command), 1);
	if (cmd)
	{
		cmd->path = path;
		cmd->argv = argv;
		cmd->fd_in = STDIN; /* default */
		cmd->fd_out = STDOUT; /* default */
	}
	return (cmd);
}

t_command	*command_destroy(t_command **cmd)
{
	if (!cmd)
		return (NULL);
	if (*cmd)
	{
		free((*cmd)->path);
		argv_destroy(&(*cmd)->argv);
		free(*cmd);
	}
	return ((*cmd = NULL));
}

void		command_set_fds(t_command *cmd, int fd_in, int fd_out)
{
	assert(cmd);
	cmd->fd_in = fd_in;
	cmd->fd_out = fd_out;
}

#include <stdio.h>

void		command_pretty_dump(t_command *cmd, int indent)
{
	assert(cmd);
	printf("%*s : %s\n", indent, "Path", cmd->path);
	argv_pretty_dump(cmd->argv, indent);
}
