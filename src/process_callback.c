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

pid_t g_ppid;

static void	__sighandler(int signal)
{
	if (signal == SIGUSR1)
		g_ready__++;
	else
		exit (signal);

	if (getpid() == g_ppid)
		dbg("RECEIVED SIGNAL FROM CHILD!!\n", "");

	dbg("Pid %i received signal %s\n", getpid(), strsignal(signal));
}

void	p_callback_register_signalhandler(int sig)
{
	g_ready__ = 0;
	p_register_signalhandler(sig, __sighandler);
	dbg("Pid %i: registered sighandler for signal %i\n", getpid(), sig);
}

void	p_callback_wait_for_signals(size_t signalcount)
{
	if (signalcount > 1)
		g_ppid = getpid();
	dbg("Pid %i: waiting until signalcounter{%i} has signalcount{%i}\n",
		getpid(), g_ready__, signalcount);
	while (g_ready__ < signalcount)
	{
		//if (signalcount > 1)
		//	dbg("Sigcount:%i\n", g_ready__);
	}
	dbg("Pid %i: signalcounter{%i} has reached signalcount{%i}!\n",
		getpid(), g_ready__, signalcount);
}
