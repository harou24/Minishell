#include "prompt.h"
#include "stdio.h"

t_prompt 	*prompt_create(const char *_username, const char *_hostname)
{
	t_prompt *prompt;

	prompt = ft_calloc(sizeof(t_prompt), 1);
	if (!prompt)
		return (NULL);
	prompt->username = ft_strdup(_username);
	prompt->hostname = ft_strdup(_hostname);
	if (!prompt->username || !prompt->hostname)
	{
		prompt_destroy(prompt);
		return (NULL);
	}
	return (prompt);
}

void 	prompt_print(t_prompt *_prompt)
{

	printf("%s@%s >", _prompt->username, _prompt->hostname);
}

void	prompt_destroy(t_prompt *_prompt)
{

	if (_prompt->username)
		free(_prompt->username);
	if (_prompt->hostname)
		free(_prompt->hostname);
	if (_prompt->current_dir)
		free(_prompt->current_dir);
	if (_prompt)
		free(_prompt);
}
