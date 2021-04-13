/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_assignment.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:03:36 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:03:42 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <stdlib.h>

#include "libft.h"
#include "debugger.h"
#include "ft_printf.h"

#include "env_singleton.h"
#include "bash_ops.h"

int	op_assignment(t_command *cmd)
{
	int		i;

	i = 0;
	while (i < cmd->argv->argc)
	{
		env_set_s_line(cmd->argv->argv[i], SCOPE_LOCAL);
		i++;
	}
	return (0);
}
