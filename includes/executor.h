#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "execscheme.h"

int					execute(t_execscheme *scheme);

/* jumptable dispatchers */
typedef int			(*relation_handler_f)(t_execscheme *scheme);
relation_handler_f	exec_relation_dispatch(t_exec_relation_type type);

typedef int			(*command_handler_f)(t_command *command);
command_handler_f	exec_command_disspatch(t_exec_op_type type);

#endif
