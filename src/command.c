/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 20:57:52 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 20:57:53 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <stdlib.h>

#include "libft.h"
#include "debugger.h"

#include "command.h"

t_bool	command_push_argument(t_command *cmd, char *arg)
{
	return (argv_push(cmd->argv, arg));
}

t_command	*command_create(char *path)
{
	t_command	*cmd;

	assert(path);
	cmd = ft_calloc(sizeof(t_command), 1);
	if (cmd)
	{
		cmd->path = path;
		cmd->argv = argv_create(ft_strdup(path));
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

void	command_pretty_dump(t_command *cmd, int indent)
{
	assert(cmd);
	dbg("%*s:\n", indent, "Command ");
	dbg("%*s: %s\n", indent, "Path ", cmd->path);
	if (cmd->argv)
		argv_pretty_dump(cmd->argv, indent);
}
