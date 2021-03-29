#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#include "debugger.h"

#include "vector.h"
#include "process.h"

static size_t	g_ready__;

static void		__sighandler(int signal)
{
	dbg("Pid %i received signal %s\n", getpid(), strsignal(signal));
	g_ready__++;
}

void	p_queue_register_signalhandler(int sig)
{
	static t_bool sighandler_registered;

	if (!sighandler_registered)
	{
		p_register_signalhandler(sig, __sighandler);
		sighandler_registered = TRUE;
	}
	g_ready__ = 0;
}

void	p_queue_wait_for_signals(size_t signalcount)
{
	while (g_ready__ < signalcount)
	;;
}
