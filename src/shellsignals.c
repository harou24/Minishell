/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shellsignals.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:07:42 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:07:43 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <stdlib.h>

#include <errno.h>
#include <setjmp.h>

#include "debugger.h"
#include "libft.h"

#include "process.h"
#include "libprintf.h"

static volatile sig_atomic_t	g_sigint__;
static volatile sig_atomic_t	g_sigint_last__;
static volatile sig_atomic_t	g_sigquit__;

static void	shell_handle_sigint(int signum)
{
	if (signum == SIGINT)
		g_sigint__++;
	else if (signum == SIGQUIT)
		g_sigquit__++;
}

int	_shell_received_signal(void)
{
	if (g_sigint__ > g_sigint_last__)
	{
		g_sigint_last__ = g_sigint__;
		return (SIGINT);
	}
	return (0);
}

int	_shell_register_sigint_handler(void)
{
	return (p_register_signalhandler(SIGQUIT, shell_handle_sigint)
		+ p_register_signalhandler(SIGINT, shell_handle_sigint));
}

void	_shell_manage_prompt_interrupts(int *last_error, char *line)
{
	if (_shell_received_signal() == SIGINT)
	{
		printf("\n");
		*last_error = 130;
	}
	else if (line == NULL)
	{
		exit (0);
	}
}

void	_shell_manage_interrupts(int *last_error)
{
	if (_shell_received_signal() == SIGINT)
		*last_error = 130;
	if (_shell_received_signal() == SIGQUIT)
		exit (0);
}
