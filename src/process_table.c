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

t_bool	p_tab_push(pid_t pid)
{
	pid_t	*pid_ptr;

	if (!g_pidvec__)
		vector(&g_pidvec__, V_CREATE, g_pidvec_def_size, NULL);
	pid_ptr = p_allocate_pid(pid);
	return (pid_ptr && vector(&g_pidvec__, V_PUSHBACK, 0, pid_ptr) != NULL);
}

t_bool	p_tab_drop(pid_t pid)
{
	pid_t	*pid_ptr;
	size_t	i;

	i = 0;
	pid_ptr = vector(&g_pidvec__, V_PEEKAT, i, NULL);
	while (pid_ptr)
	{
		if (*pid_ptr == pid)
		{
			free(vector(&g_pidvec__, V_POPAT, i, NULL));
			return (TRUE);
		}
		i++;
		pid_ptr = vector(&g_pidvec__, V_PEEKAT, i, NULL);
	}
	return (FALSE);
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

int	p_tab_wait_all(t_waitcond cond)
{
	size_t	i;
	int		status;
	pid_t	*pid;

	assert(g_pidvec__);
	i = 0;
	pid = vector(&g_pidvec__, V_PEEKAT, i++, NULL);
	while (pid)
	{
		status = p_wait(pid, cond);
		p_tab_drop(*pid);
		if (status == -1)
			return (status);
			
		pid = vector(&g_pidvec__, V_PEEKAT, i++, NULL);
	}
	return (0);
}

int	p_tab_signal_all(int signal)
{
	int		_err;
	size_t	i;

	if (!g_pidvec__)
		return (0);
	_err = 0;
	i = 0;
	while (i < p_tab_size())
	{
		if (p_signal(p_tab_at(i), signal) != 0)
			_err = errno;
		i++;
	}
	return (_err);
}

int	p_tab_drop_all(void)
{
	int		_err;

	if (!g_pidvec__)
		return (0);
	_err = 0;
	while (p_tab_size() > 0)
		free(vector(&g_pidvec__, V_POPBACK, 0, NULL));
	assert(p_tab_size() == 0);
	return (_err);
}
