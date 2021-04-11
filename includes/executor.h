#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "execscheme.h"

int					execute(t_execscheme *scheme);
void	executor_launch_parallel_scheme(pid_t pid);
int	executor_launch_sequential_scheme(t_execscheme *scheme, pid_t pid);
/* jumptable dispatchers */
typedef int			(*relation_handler_f)(t_execscheme *scheme);
relation_handler_f	execscheme_dispatch(t_exec_relation_type type);

typedef int			(*command_handler_f)(t_command *command);
command_handler_f	command_dispatch(t_exec_op_type type);

/* execscheme handlers */
int		handler_scheme_seq(t_execscheme *scheme);
int		handler_scheme_pipe(t_execscheme *scheme);
int		handler_scheme_redirection(t_execscheme *scheme);

/* redirection handlers */
t_bool	redirection_stdout_to_pipe(const char *fname, t_bool should_append);
t_bool	redirection_file_to_stdin(const char *fname);
t_bool	redirection_pipe_to_stdin(int pipe[2]);

void	executor_kill_all(t_execscheme *scheme);
t_bool	executor_should_run_in_parent(t_execscheme *scheme);

#endif
