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

static int	signal_status(t_waitcond cond, int status)
{
	if (cond == W_EXITED)
		return (WEXITSTATUS(status));
	else if (cond == W_TERMINATED)
		return (WTERMSIG(status));
	else if (cond == W_ABORTED)
		return (WCOREDUMP(status));
	else
		assert(!"UNDEFINED WAIT CONDITION");
	return (FALSE);
}

static void	dump_signal_status(int status, pid_t pid)
{
	if (WIFEXITED(status))
		dbg("Pid %i exited with status %i!\n", pid, WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		dbg("Pid %i was terminated with status %i!\n", pid, WTERMSIG(status));
	else if (WIFSIGNALED(status) && WCOREDUMP(status))
		dbg("Pid %i was aborted with status %i!\n", pid, WCOREDUMP(status));
	else
		dbg("Pid %i has illegal status!\n", pid);
}

int	p_wait(pid_t *pid, t_waitcond cond)
{
	int	status;

	if (cond == W_EXITED)
		dbg("Waiting for pid %i to exit\n", pid);
	waitpid(*pid, &status, 0);
	dump_signal_status(status, *pid);
	if (signal_status(cond, status) == -1)
		*pid = -1;
	else
		*pid = 0;
	return (signal_status(cond, status));
}

int	p_signal(pid_t pid, int signal)
{
	int	error;

	if (kill(pid, 0) == -1)
	{
		dbg("Not allowed to send signal %s to pid %i, errno: %s\n",
			strsignal(signal), pid, strerror(errno));
		return (-1);
	}
	error = kill(pid, signal);
	if (error == -1)
	{
		dbg("couldn't send signal %s to pid %i, errno: %s\n",
			strsignal(signal), pid, strerror(errno));
	}
	else
	{
		dbg("Succesfully sent signal %s to pid %i (from pid: %i)\n",
			strsignal(signal), pid, getpid());
	}
	return (error);
}

int	p_register_signalhandler(int sig, void (*sighandler)(int sig))
{
	struct sigaction	sa;

	sa.sa_handler = sighandler;
	if (sigaction(sig, &sa, 0) == -1)
		return (-1);
	return (0);
}
