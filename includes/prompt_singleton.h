#ifndef PROMPT_SINGLETON_H
# define PROMPT_SINGLETON_H

# include "libft.h"
# include "prompt.h"

t_prompt	*prompt_init(void);
void		prompt_deinit(t_prompt **prompt);

char		*prompt(int last_error);

#endif
