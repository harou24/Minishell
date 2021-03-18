#include <assert.h>
#include <stdlib.h>

#include "bash_ops.h"
#include "command.h"
#include "execscheme.h"
#include "executor.h"

/* remove stub function when ready */
static int					rel_stub(t_execscheme *scheme) {(void)scheme; return (-1);}

static int	(*g_schemetab__[REL_TAB_SIZE])(t_execscheme *scheme) =	{
																[REL_START] = handler_scheme_seq,
																[REL_SEQ] = handler_scheme_seq,
																[REL_PIPE] = handler_scheme_pipe,
																[REL_READ] = rel_stub,
																[REL_APPEND] = rel_stub,
																[REL_WRITE] = rel_stub,
																[REL_NO_TYPE] = rel_stub,
																[REL_END] = handler_scheme_seq
															};

/* remove stub function when ready */
static int				op_stub(t_command *cmd) {(void)cmd; return (-1);}

static int	(*g_comtab__[OP_TAB_SIZE])(t_command *cmd) =		{
																[OP_COMMAND] = exec_bin,
																[OP_PATH] = op_stub,
																[OP_ASSIGNMENT] = op_stub,
																[OP_BUILTIN_ECHO] = builtin_echo,
																[OP_BUILTIN_CD] = builtin_cd,
																[OP_BUILTIN_PWD] = op_stub,
																[OP_BUILTIN_EXPORT] = op_stub,
																[OP_BUILTIN_UNSET] = op_stub,
																[OP_BUILTIN_ENV] = op_stub,
																[OP_BUILTIN_EXIT] = op_stub,
																[OP_NO_TYPE] = op_stub
															};

relation_handler_f		execscheme_dispatch(t_exec_relation_type type)
{
	return (g_schemetab__[type]);
}

command_handler_f		command_dispatch(t_exec_op_type type)
{
	return (g_comtab__[type]);
}
