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
	prompt->buffer = ft_calloc(sizeof(char), BUFFER_SIZE);
	if (!prompt->buffer || !prompt->username || !prompt->hostname)
	{
		prompt_destroy(prompt);
		return (NULL);
	}
	/*prompt->current_path = directory_get_current_path();  -> first need to merge directory branch*/
	prompt->error_code = 0;
	prompt_init_buffer(prompt);
	return (prompt);
}

void	prompt_init_buffer(t_prompt *_prompt)
{
	if (_prompt->error_code != 0)
		snprintf(_prompt->buffer, ERROR_LENGTH, "%d", _prompt->error_code);
	else
		snprintf(_prompt->buffer, ERROR_LENGTH, "   ");
	snprintf(_prompt->buffer, PROMPT_LENGTH, " %s@%s:[%s]>", _prompt->username, _prompt->hostname, _prompt->current_path);		
}
/*
void	prompt_update_current_path(t_prompt *_prompt)
{
	_prompt->current_path = directory_get_current_path();	
}
*/
void	prompt_set_error_code(t_prompt *_prompt, int _error_code)
{
	_prompt->error_code = _error_code;
}

void	set_current_path(t_prompt *_prompt, const char *_path)
{
	_prompt->current_path = (char *)_path;
}

void 	prompt_print(t_prompt *_prompt)
{
	printf("%s@%s >", _prompt->username, _prompt->hostname);
	printf("%s", _prompt->buffer);
}

void	prompt_destroy(t_prompt *_prompt)
{

	if (_prompt->username)
		free(_prompt->username);
	if (_prompt->hostname)
		free(_prompt->hostname);
	if (_prompt->current_path)
		free(_prompt->current_path);
}
