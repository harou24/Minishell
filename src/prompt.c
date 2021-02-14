#include "prompt.h"

void	*new_prompt(const char *_username, const char *_hostname)
{
	t_prompt *prompt;

	prompt = ft_calloc(sizeof(t_prompt), 1);
	prompt->username = ft_strdup(_username);
	prompt->hostname = ft_strdup(_hostname);
	return ((void *) prompt);
}

void	print_prompt(void *_prompt)
{
	t_prompt *prompt;

	prompt = (t_prompt *)_prompt;
	ft_putstr_fd(prompt->username, 1);
	ft_putchar_fd('@', 1);
	ft_putstr(prompt->hostname, 1);
	ft_putchar_fd('>', 1)
	ft_putchar_fd('\n', 1);
}
