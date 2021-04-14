/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_exit.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 20:57:32 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 20:57:34 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "bash_ops.h"
#include <stdlib.h>

int	builtin_exit(t_command *cmd)
{
	unsigned int	exit_status;

	if (cmd->argv->argc == 2)
	{
		exit_status = ft_atoi(cmd->argv->argv[1]);
		if (exit_status > 255)
			exit (255);
		exit (exit_status);
	}
	else if (cmd->argv->argc == 1)
		exit(0);
	exit(128);
}
