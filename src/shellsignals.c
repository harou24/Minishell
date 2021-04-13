#include <assert.h>
#include <stdlib.h>

#include <setjmp.h>

#include "debugger.h"
#include "libft.h"

#include "process.h"
#include "libprintf.h"

static volatile int		g_sigint__;
static volatile int		g_sigint_last__;
static volatile int		g_sigquit__;

static void	shell_handle_sigint(int signum)
{
	dbg("Shell caught signal: %i\n", signum);
	if (signum == SIGINT)
		g_sigint__++;
	else if (signum == SIGQUIT)
		g_sigquit__++;
}

int	_shell_received_signal(void)
{
	if (g_sigquit__ > 0)
		return (SIGQUIT);
	if (g_sigint__ > g_sigint_last__)
	{
		g_sigint_last__ = g_sigint__;
		return(SIGINT);
	}
	return (0);
}

int	_shell_register_sigint_handler(void)
{
	p_register_signalhandler(SIGQUIT, shell_handle_sigint);
	return (p_register_signalhandler(SIGINT, shell_handle_sigint));
}

void		_shell_manage_prompt_interrupts(int *last_error, char *line)
{
	if (line == NULL && _shell_received_signal() == SIGINT)
	{
		*last_error = 130;
		ft_dprintf(STDERR, "\n");
	}
	else if (line == NULL)
		exit (0);
}

void		_shell_manage_interrupts(int *last_error)
{
	if (_shell_received_signal() == SIGINT)
		*last_error = 130;
	if (_shell_received_signal() == SIGQUIT)
		exit (0);
}
