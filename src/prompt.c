#include "prompt.h"

void	*prompt_create(const char *_username, const char *_hostname)
{
	t_prompt *prompt;

	prompt = ft_calloc(sizeof(t_prompt), 1);
	if (!prompt)
		return (NULL);
	prompt->username = ft_strdup(_username);
	prompt->hostname = ft_strdup(_hostname);
	if (!prompt->username || !prompt->hostname)
	{
		prompt->destroy((void *)prompt);
		return (NULL);
	}
	return ((void *) prompt);
}

void	prompt_print(void *_prompt)
{
	t_prompt *prompt;

	prompt = (t_prompt *)_prompt;
	ft_putstr_fd(prompt->username, 1);
	ft_putchar_fd('@', 1);
	ft_putstr(prompt->hostname, 1);
	ft_putchar_fd('>', 1)
	ft_putchar_fd('\n', 1);
}

void	prompt_destroy(void *_prompt)
{
	t_prompt *prompt;

	prompt = (t_prompt *)_prompt;
	if (prompt->username)
		free(prompt->username)
	if (prompt->hostname)
		free(prompt->hostname);
	if (prompt->current_directory)
		free(prompt->current_directory);
	if (prompt)
		free(prompt);
}
