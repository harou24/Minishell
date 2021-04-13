/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_signalling.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:01:28 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:01:30 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "executor.h"

void	executor_kill_all(t_execscheme *scheme)
{
	while (scheme)
	{
		if (scheme->pid > 0)
		{
			p_signal(scheme->pid, SIGTERM);
			scheme->pid = -1;
		}
		scheme = scheme->next;
	}
}
