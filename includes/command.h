/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:09:02 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:09:03 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "argv.h"

typedef struct s_command
{
	char	*path;
	t_argv	*argv;
}				t_command;

t_bool			command_push_argument(t_command *cmd, char *arg);
t_command		*command_create(char *path);
t_command		*command_destroy(t_command **_command);

void			command_pretty_dump(t_command *cmd, int indent);
#endif
