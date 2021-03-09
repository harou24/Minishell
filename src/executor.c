#include <assert.h>
#include <stdlib.h>

#include <sys/wait.h>
#include <unistd.h>

#include "libft.h"
#include "debugger.h"

#include "command.h"
#include "executor.h"

typedef struct		s_op
{
	t_exec_op_type	type;
	int				(*f)(t_command *cmd);
}					t_op;

/* remove stub function when ready */
static int			op_stub(t_command *cmd) {(void)cmd; return (-1);}

static int	(*g_optab__[OP_TAB_SIZE])(t_command *cmd) =	{
	[OP_COMMAND] = op_stub,
	[OP_PATH] = op_stub,
	[OP_ASSIGNMENT] = op_stub,
	[OP_BUILTIN_ECHO] = op_stub,
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
	int	error;

	error = 0;
	while (scheme)
	{
		/*
			1. handle op type
			2. setup fd's
			3. fork()
			4. execute
		*/
		error = g_optab__[scheme->op_type](scheme->cmd);

		/* handle error */

		scheme = scheme->next;
	}
	return (error);
}
