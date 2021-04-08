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

int	p_pause(void)
{
	pause();
	if (errno == EINTR)
		dbg("pid %i caught and handled signal, continuing..\n", getpid());
	return (0);
}

static t_bool	__correct_signal(t_waitcond cond, int status)
{
	if (cond == W_EXITED)
		return (WIFEXITED(status));
	else if (cond == W_TERMINATED)
		return (WIFSIGNALED(status));
	else if (cond == W_ABORTED)
		return (WIFSIGNALED(status) && WCOREDUMP(status));
	else
		assert(!"UNDEFINED WAIT CONDITION");
	return (FALSE);
}

static int	__return_signal_status(t_waitcond cond, int status)
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

int	p_waitpid(pid_t pid, t_waitcond cond)
{
	int	status;

	if (cond == W_EXITED)
		dbg("waiting for pid %i to exit\n", pid);
	while (waitpid(pid, &status, 0) <= 0 && !__correct_signal(cond, status))
	{
	}
	if (cond == WEXITED)
		dbg("pid %i exited with status %i!\n", pid, WEXITSTATUS(pid));
	return (__return_signal_status(cond, status));
}

int	p_signal(pid_t pid, int signal)
{
	int	error;

	error = kill(pid, signal);
	if (error == -1)
	{
		dbg("couldn't send signal %s to pid %i, errno: %s\n",
			strsignal(signal), pid, strerror(errno));
	}
	return (error);
}
