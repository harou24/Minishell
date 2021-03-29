#include <assert.h>
#include <stdlib.h>

#include <setjmp.h>

#include "debugger.h"
#include "libft.h"

#include "process.h"
#include "libprintf.h"

static jmp_buf g_jmpbuf__;

static volatile int g_sigint__;
static int g_sigint_last__;

static void	shell_handle_sigint(int signum)
{
	p_tab_signal_all(SIGTERM);
	g_sigint__++;
	(void)signum;
}

t_bool		_shell_was_interrupted()
{
	t_bool	was_interrupted;

	was_interrupted = FALSE;
	if (g_sigint__ > g_sigint_last__)
	{
		was_interrupted = TRUE;
	}
	g_sigint_last__ = g_sigint__;
	return (was_interrupted);
}

int			_shell_register_sigint_handler(void)
{
	p_register_signalhandler(SIGQUIT, shell_handle_sigint);
	return(p_register_signalhandler(SIGINT, shell_handle_sigint));
}

jmp_buf		*_shell_get_interrupt_jmpbuf(void)
{
	return (&g_jmpbuf__);
}
