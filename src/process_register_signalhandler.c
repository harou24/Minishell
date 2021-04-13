#include <errno.h>
#include <string.h>

#include <signal.h>

#include "debugger.h"

#include "process.h"

int	p_register_signalhandler(int sig, void (*sighandler)(int sig))
{
	if (signal(sig, sighandler) == SIG_ERR)
	{
		dbg("Failed to register handler for signum: %i, with errno: %s\n",
			sig, strerror(errno));
		return (-1);
	}
	else
	{
		dbg("Succesfully registered handler for signum: %i for pid %i\n",
			sig, getpid());
	}
	return (0);
}

