#ifndef PROMPT_H
# define PROMPT_H

#include "libft.h"
#include <stdlib.h>

typedef struct	s_prompt
{
		char *username;
		char *hostname;
		char *current_path;
}		t_prompt;

void	*prompt_create(const char *_username, const char *_hostname);
void	prompt_print(void *_prompt);
void	prompt_destroy(void *_prompt);

#endif
