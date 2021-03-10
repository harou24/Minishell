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

int		pid_wait_all()
{
	int		status;
	size_t	i;
	pid_t	*pid;

	assert(g_pidvec__);
	i = 0;
	while ((pid = vector(&g_pidvec__, V_PEEKAT, i++, NULL)))
	{
		waitpid(*pid, &status, 0);
		if (WIFEXITED(status))
		{
			/* process exited */
			if (WEXITSTATUS(status) != 0)
				return (WEXITSTATUS(status));
		}
		else
		{
			/* handle anomaly */
			return (-1);
		}
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
		if (kill(*pid, SIGTERM) == -1)
			_err = errno;
		free(pid);
	}
	return (_err);
}
