/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:09:37 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:09:38 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "execscheme.h"

int						execute(t_execscheme *scheme);
void					executor_launch_parallel_scheme(pid_t pid);
int						executor_launch_sequential_scheme(t_execscheme *scheme,
							pid_t pid);
/* jumptable dispatchers */
typedef int				(*t_relation_handler_f)(t_execscheme *scheme);
t_relation_handler_f	execscheme_dispatch(t_exec_relation_type type);

typedef int				(*t_command_handler_f)(t_command *command);
t_command_handler_f		command_dispatch(t_exec_op_type type);

/* execscheme handlers */
int						handler_scheme_seq(t_execscheme *scheme);
int						handler_scheme_pipe(t_execscheme *scheme);

t_bool					executor_handle_redirections_pre(t_execscheme *scheme);
t_bool					executor_handle_redirections_post(t_execscheme *scheme);

void					executor_kill_all(t_execscheme *scheme);
t_bool					executor_should_run_in_parent(t_execscheme *scheme);

#endif
