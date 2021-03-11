#include <assert.h>
#include <stdlib.h>
#include <errno.h>

#include <signal.h>
#include <sys/wait.h>

#include "vector.h"
#include "pid.h"

const size_t pidvec_def_size = 16;

static void *g_pidvec__;

static void	__pidvec_init()
{
	if (g_pidvec__)
		return ;
	assert(vector(&g_pidvec__, V_CREATE, pidvec_def_size, NULL));
}

pid_t	*pid_allocate(pid_t pid)
{
	return ((pid_t *)ft_memdup(&pid, sizeof(pid_t)));
}

t_bool	pid_push(pid_t *pid)
{
	__pidvec_init();
	return (vector(&g_pidvec__, V_PUSHBACK, 0, pid) != NULL);
}

pid_t	pid_last()
{
	pid_t	*pid;

	if (g_pidvec__)
	{
		pid = vector(&g_pidvec__, V_PEEKBACK, 0, NULL);
		if (pid)
			return (*pid);
	}
	return (0);
}

int		pid_wait(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		/* process exited */
		return (WEXITSTATUS(status));
	}
	else
	{
		/* handle anomaly */
		return (-1);
	}
}

int		pid_kill(pid_t pid)
{
	if (kill(pid, SIGTERM) == -1)
		return(errno);
	return (0);
}

int		pid_wait_all()
{
	size_t	i;
	pid_t	*pid;

	assert(g_pidvec__);
	i = 0;
	while ((pid = vector(&g_pidvec__, V_PEEKAT, i++, NULL)))
	{
		pid_wait(*pid);
	}
	return (0);
}

int		pid_kill_all()
{
	int		_err;
	pid_t	*pid;

	assert(g_pidvec__);
	_err = 0;
	while((pid = vector(&g_pidvec__, V_POPBACK, 0, NULL)))
	{
		if (pid_kill(*pid) != 0)
			_err = errno;
		free(pid);
	}
	return (_err);
}
