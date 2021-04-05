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
	struct sigaction	sa;

	sa.sa_handler = sighandler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(sig, &sa, NULL) == -1)
	{
		dbg("couldn't register handler for signal %s, errno: %s\n",
			strsignal(sig), strerror(errno));
		return (-1);
	}
	return (0);
}
