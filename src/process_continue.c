#include <errno.h>
#include <string.h>

#include <signal.h>

#include "debugger.h"

#include "process.h"

pid_t	*p_allocate_pid(pid_t pid)
{
	return ((pid_t *)ft_memdup(&pid, sizeof(pid_t)));
}

int	p_register_signalhandler(int sig, void (*sighandler)(int sig))
{
	if (signal(sig, sighandler) == SIG_ERR)
	{
		dbg("Failed to register handler for signum: %i, with errno: %s\n", sig, strerror(errno));
		return (-1);
	}
	return (0);
}
