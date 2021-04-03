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

const size_t	g_pidvec_def_size = 16;
static void		*g_pidvec__;

static void	__pidvec_init(void)
{
	if (g_pidvec__)
		return ;
	assert(vector(&g_pidvec__, V_CREATE, g_pidvec_def_size, NULL));
}

t_bool	p_tab_push(pid_t pid)
{
	pid_t	*pid_ptr;

	__pidvec_init();
	pid_ptr = p_allocate_pid(pid);
	if (!pid_ptr)
		return (FALSE);
	return (vector(&g_pidvec__, V_PUSHBACK, 0, pid_ptr) != NULL);
}

pid_t	p_tab_at(size_t index)
{
	pid_t	*pid;

	if (g_pidvec__)
	{
		pid = vector(&g_pidvec__, V_PEEKAT, index, NULL);
		if (pid)
			return (*pid);
	}
	return (-1);
}

size_t	p_tab_size(void)
{
	if (g_pidvec__)
		return (*(size_t *)vector(&g_pidvec__, V_SIZE, 0, NULL));
	return (0);
}

int	p_tab_waitpid_all(t_waitcond cond)
{
	size_t	i;
	pid_t	*pid;

	assert(g_pidvec__);
	i = 0;
	while ((pid = vector(&g_pidvec__, V_PEEKAT, i++, NULL)))
	{
		p_waitpid(*pid, cond);
	}
	return (0);
}

int	p_tab_signal_all(int signal)
{
	int		_err;
	pid_t	*pid;

	if (!g_pidvec__)
		return (0);
	_err = 0;
	while ((pid = vector(&g_pidvec__, V_POPBACK, 0, NULL)))
	{
		if (p_signal(*pid, signal) != 0)
			_err = errno;
		free(pid);
	}
	assert(*(size_t *)vector(&g_pidvec__, V_SIZE, 0, NULL) == 0);
	return (_err);
}
