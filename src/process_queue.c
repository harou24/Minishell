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

static volatile size_t	g_ready__;

static void	__sighandler(int signal)
{
	if (signal == SIGUSR1)
		g_ready__++;
	dbg("Pid %i received signal %s\n", getpid(), strsignal(signal));
}

void	p_queue_register_signalhandler(int sig)
{
	g_ready__ = 0;
	p_register_signalhandler(sig, __sighandler);
	dbg("Registed sighandler for signal %i\n", sig);
}

void	p_queue_wait_for_signals(size_t signalcount)
{
	dbg("Waiting until signalcounter{%i} has reached signalcount{%i}\n", g_ready__, signalcount);
	while (g_ready__ < signalcount)
	{
	}
	dbg("Signalcounter{%i} has reached signalcount{%i}!\n", g_ready__, signalcount);
}
