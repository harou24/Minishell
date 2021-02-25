#ifndef SHELL_H
# define SHELL_H

#include "env.h"
#include "prompt.h"

typedef struct	s_shell {
		t_env		*env;
		t_prompt	*prompt;
}		t_shell;

t_shell		*shell_create(const char **_env);
void		shell_update_prompt(t_shell *shell);
void		shell_display_prompt(t_shell *shell);
void		shell_destroy(t_shell *shell);

#endif
