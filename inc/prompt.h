#ifndef PROMPT_H
# define PROMPT_H

#include "libft.h"
#include <stdlib.h>

typedef struct	s_prompt
{
	char	*buffer;
}		t_prompt;

void	*new_prompt(const char *_prompt_str);
void	set_prompt(void *_prompt, char *_prompt_str);
void	print_prompt(void *_prompt);

#endif
