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

void	*new_prompt(const char *_username, const char *_hostname);
void	print_prompt(void *_prompt);

#endif
