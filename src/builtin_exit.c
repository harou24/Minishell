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

	if (argv_get_size(cmd->argv) == 2)
	{
		exit_status = ft_atoi(argv_get(cmd->argv, 1));
		exit (exit_status);
	}
	else if (argv_get_size(cmd->argv) == 1)
		exit(0);
	exit(128);
}
