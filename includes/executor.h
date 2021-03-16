#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "execscheme.h"

int					execute(t_execscheme *scheme);

/* jumptable dispatchers */
typedef int			(*relation_handler_f)(t_execscheme **scheme);
relation_handler_f	execscheme_dispatch(t_exec_relation_type type);

typedef int			(*command_handler_f)(t_command *command);
command_handler_f	command_dispatch(t_exec_op_type type);

/* execscheme handlers */
int		handler_scheme_seq(t_execscheme **scheme);
int		handler_scheme_pipe(t_execscheme **scheme);

#endif
