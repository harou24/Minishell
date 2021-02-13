#include "prompt.h"

void	*new_prompt(const char *_prompt_str)
{
	t_prompt *prompt;

	prompt = ft_calloc(sizeof(t_prompt), 1);
	prompt->buffer = ft_strdup(_prompt_str);
	return ((void *) prompt);
}

void	set_prompt(void *_prompt, char *_prompt_str)
{
	t_prompt *prompt;

	prompt = (t_prompt *)_prompt;
	if (prompt->buffer)
		free(prompt->buffer);
	prompt->buffer = 
	ft_strdup(_prompt_str);
}

void	print_prompt(void *_prompt)
{
	t_prompt *prompt;

	prompt = (t_prompt *)_prompt;
	ft_putstr_fd(prompt->buffer, 1);
}
