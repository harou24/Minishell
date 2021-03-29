#ifndef SHELLCORE_H
# define SHELLCORE_H

#include "minishell.h"

#include <setjmp.h>

#include "env.h"
#include "lexer.h"
#include "parser.h"
#include "prompt.h"

typedef struct	s_shell
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

/* shellsignals.c */

t_bool			_shell_was_interrupted();
int				_shell_register_sigint_handler(void);
jmp_buf			*_shell_get_interrupt_jmpbuf(void);
#endif
