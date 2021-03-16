#include <assert.h>
#include <stdlib.h>

#include <sys/wait.h>
#include <unistd.h>

#include "libft.h"
#include "debugger.h"

#include "command.h"
#include "process.h"
#include "executor.h"

#include "bash_ops.h"

#include <stdio.h>
#include <string.h>

static int	__execute_sequentially()
{
	int		error;
	size_t	i;

	dbg("signalling all children...%s\n","");

	error = 0;
	i = 0;
	while (p_tab_at(i) > 0)
	{
		p_signal(p_tab_at(i), SIGUSR1);
		error = p_waitpid(p_tab_at(i), W_EXITED);
		if (error != 0)
			break;
		i++;
	}
	return (error);
}

int			execute(t_execscheme *scheme)
{
	int		error;

	error = 0;
	p_queue_register_signalhandler(SIGUSR1);
	while (scheme)
	{
		/* dispatch for execscheme type */
		dbg("executing scheme: %s, %s <- relation -> %s\n", execscheme_dump_op_type(scheme->op_type), execscheme_dump_relation_type(scheme->rel_type[PREV_R]), execscheme_dump_relation_type(scheme->rel_type[NEXT_R]));
		if (execscheme_dispatch(scheme->rel_type[NEXT_R])(&scheme) != 0)
		{
			dbg("%s\n", "failed to execute scheme !");
			p_tab_signal_all(SIGTERM);
			return (-1);
		}
		scheme = scheme->next;
	}

	/* wait for children to register signal handlers */
	p_queue_wait_for_signals(p_tab_size());

	error = __execute_sequentially();

	/* kill the kids */
	p_tab_signal_all(SIGTERM);
	return (error);
}
