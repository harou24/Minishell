#include <stdio.h>
#include <stdlib.h>
#include "directory.h"
#include "prompt.h"
#include "libft.h"

#define __PROMPT_BUFF_SIZE 255
#define	__PROMPT_MAX_LENGTH 1024
#define __ERROR_LENGTH 4

t_prompt 	*prompt_create(const char *_username, const char *_hostname)
{
	t_prompt *prompt;

	prompt = ft_calloc(sizeof(t_prompt), 1);
	if (!prompt)
		return (NULL);
	prompt->username = ft_strdup(_username);
	prompt->hostname = ft_strdup(_hostname);
	prompt->error_code = 0;
	prompt->buffer = ft_calloc(sizeof(char), __PROMPT_BUFF_SIZE);
	prompt->current_path = directory_get_current_dir();
	if (!prompt->current_path || !prompt->buffer || !prompt->username || !prompt->hostname)
	{
		prompt_destroy(prompt);
		return (NULL);
	}
	prompt_init_indexes(prompt);
	prompt_init_buffer(prompt);
	return (prompt);
}

void	prompt_init_indexes(t_prompt *_prompt)
{
	_prompt->error_index = 0;
	_prompt->user_index = 3;
	_prompt->at_index = _prompt->user_index + ft_strlen(_prompt->username);
	_prompt->host_index = _prompt->at_index + 1;
	_prompt->colon_index = _prompt->host_index + ft_strlen(_prompt->hostname);
	_prompt->path_index = _prompt->colon_index + 1;
	_prompt->bracket_index = _prompt->path_index + ft_strlen(_prompt->current_path);
}

void	prompt_init_buffer(t_prompt *_prompt)
{
	if (_prompt->error_code != 0)
		snprintf(_prompt->buffer, __ERROR_LENGTH, "%d", _prompt->error_code);
	else
		snprintf(_prompt->buffer, __ERROR_LENGTH, "---");
	snprintf(_prompt->buffer + _prompt->user_index, ft_strlen(_prompt->username) + 1, "%s", _prompt->username);
	snprintf(_prompt->buffer + _prompt->at_index , 2, "@");
	snprintf(_prompt->buffer + _prompt->host_index, ft_strlen(_prompt->hostname) + 1, "%s", _prompt->hostname);
	snprintf(_prompt->buffer + _prompt->colon_index, 2, ":");
	snprintf(_prompt->buffer + _prompt->path_index, ft_strlen(_prompt->current_path) + 1, "%s", _prompt->current_path);
	snprintf(_prompt->buffer + _prompt->bracket_index, 2, ">");
}

void	prompt_update_current_path(t_prompt *_prompt)
{
	_prompt->current_path = directory_get_current_dir();	
}

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
	if (_prompt->buffer)
		free(_prompt->buffer);
	free(_prompt);
}