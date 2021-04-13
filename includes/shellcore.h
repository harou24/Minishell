/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shellcore.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:10:33 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:10:34 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELLCORE_H
# define SHELLCORE_H

# include "minishell.h"

# include <setjmp.h>

# include "env.h"
# include "lexer.h"
# include "parser.h"
# include "prompt.h"

typedef struct s_shell
{
	t_env		*env;
	t_lex		*lexer;
	t_parser	*parser;
	t_prompt	*prompt;
}				t_shell;

t_shell			*_shell_create(char **env);
t_shell			*_shell_destroy(t_shell **shell);

int				_shell_exec(t_shell *shell, const char *command_string);

t_shellerr		_shell_loop(t_shell *shell);
t_bool			__shell_load_process_env(void);

/* shellsignals.c */

int				_shell_received_signal(void);
int				_shell_register_sigint_handler(void);
void			_shell_manage_interrupts(int *last_error);
void			_shell_manage_prompt_interrupts(int *last_error, char *line);
#endif
