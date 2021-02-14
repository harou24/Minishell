#ifndef PROMPT_H
# define PROMPT_H

#include "libft.h"
#include <stdlib.h>

typedef struct	s_prompt
{
		char *username;
		char *hostname;
		char *current_dir;
}		t_prompt;

t_prompt	*prompt_create(const char *_username, const char *_hostname);
void		set_current_dir(const char *_path);
void		prompt_print(t_prompt *_prompt);
void		prompt_destroy(t_prompt *_prompt);

#endif
