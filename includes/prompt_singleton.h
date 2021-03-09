#ifndef PROMPT_SINGLETON_H
# define PROMPT_SINGLETON_H

#include "libft.h"
#include "prompt.h"

t_prompt	*prompt_init();
void		prompt_deinit();

char		*prompt(int last_error);

#endif
