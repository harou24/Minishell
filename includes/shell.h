#ifndef SHELL_H
# define SHELL_H

#include "prompt.h"
#include "hashmap.h"

typedef struct 	s_shell {
		t_prompt	*prompt;
		void		*hm_env;		
}		t_shell;

t_shell		*shell_create(const char *_username, const char *_hostname);
void		*shell_get_env(void);
void		shell_destroy(t_shell *shell);

#endif
