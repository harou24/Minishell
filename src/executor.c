#include <assert.h>
#include <stdlib.h>

#include <sys/wait.h>
#include <unistd.h>

#include "libft.h"
#include "debugger.h"

#include "command.h"
#include "pid.h"
#include "executor.h"

#include "bash_ops.h"

typedef struct		s_op
{
	t_exec_op_type	type;
	int				(*f)(t_command *cmd);
}					t_op;

/* remove stub function when ready */
static int			op_stub(t_command *cmd) {(void)cmd; return (-1);}

static int	(*g_optab__[OP_TAB_SIZE])(t_command *cmd) =	{
	[OP_COMMAND] = exec_bin,
	[OP_PATH] = op_stub,
	[OP_ASSIGNMENT] = op_stub,
	[OP_BUILTIN_ECHO] = builtin_echo,
	[OP_BUILTIN_CD] = op_stub,
	[OP_BUILTIN_PWD] = op_stub,
	[OP_BUILTIN_EXPORT] = op_stub,
	[OP_BUILTIN_UNSET] = op_stub,
	[OP_BUILTIN_ENV] = op_stub,
	[OP_BUILTIN_EXIT] = op_stub,
	[OP_NO_TYPE] = op_stub
	};

int		execute(t_execscheme *scheme)
{
	int		error;
	pid_t	pid;

	error = 0;
	while (scheme)
	{
		/*
			1. handle op type
			2. setup fd's
			3. fork()
			4. execute
		*/
		pid = fork();
		if (pid == 0)
		{
			/* child */
			g_optab__[scheme->op_type](scheme->cmd);
			dbg("%s\n", "child process didn't exit!");
			abort();
		}
		else
		{
			/* parent */
			/* store pid in vec */
			pid_push(pid_allocate(pid));
		}

		/* handle error */

		scheme = scheme->next;
	}
	/* wait for all child processes to finish,  or kill processes when process returns non-zero */
	error = pid_wait_all();
	pid_kill_all();
	return (error);
}
