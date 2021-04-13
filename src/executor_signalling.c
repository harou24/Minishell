#include "process.h"
#include "executor.h"

void	executor_kill_all(t_execscheme *scheme)
{
	while (scheme)
	{
		if (scheme->pid > 0)
		{
			p_signal(scheme->pid, SIGTERM);
			scheme->pid = -1;
		}
		scheme = scheme->next;
	}
}
