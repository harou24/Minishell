#include <assert.h>
#include <stdlib.h>

#include "libft.h"
#include "get_next_line.h"
#include "ft_printf.h"

#include "env_singleton.h"
#include "filesystem.h"
#include "filesystem_traversal.h"
#include "prompt.h"

#define __PROMPT_BUFF_SIZE 255
#define	__PROMPT_MAX_LENGTH 1024
#define __ERROR_LENGTH 4

t_prompt 	*prompt_create(const char *_username, const char *_hostname)
{
	t_prompt	*prompt;

	assert(_username);
	assert(_hostname);
	prompt = ft_calloc(sizeof(t_prompt), 1);
	if (!prompt)
		return (NULL);
	prompt->username = ft_strdup(_username);
	prompt->hostname = ft_strdup(_hostname);
	prompt->error_code = 0;
	prompt->buffer = ft_calloc(sizeof(char), __PROMPT_BUFF_SIZE);
	prompt->current_path = fs_get_cur_dir_name();
	if (!prompt->current_path || !prompt->buffer
		|| !prompt->username || !prompt->hostname)
	{
		prompt_destroy(prompt);
		return (NULL);
	}
	prompt_init_indexes(prompt);
	prompt_prepare_buffer(prompt);
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

void	prompt_prepare_buffer(t_prompt *_prompt)
{
	ft_snprintf(_prompt->buffer, __ERROR_LENGTH, "%-*d", __ERROR_LENGTH,_prompt->error_code);
	ft_snprintf(_prompt->buffer + _prompt->user_index, ft_strlen(_prompt->username) + 1, "%s", _prompt->username);
	ft_snprintf(_prompt->buffer + _prompt->at_index , 2, "@");
	ft_snprintf(_prompt->buffer + _prompt->host_index, ft_strlen(_prompt->hostname) + 1, "%s", _prompt->hostname);
	ft_snprintf(_prompt->buffer + _prompt->colon_index, 2, ":");
	ft_snprintf(_prompt->buffer + _prompt->path_index, ft_strlen(_prompt->current_path) + 1, "%s", _prompt->current_path);
	ft_snprintf(_prompt->buffer + _prompt->bracket_index, 3, "> ");
}

int	prompt_update_current_path(t_prompt *_prompt)
{
	free(_prompt->current_path);
	_prompt->current_path = fs_get_cur_dir_name();
	if (!_prompt->current_path)
		return (0);
	return (1);
}

void	prompt_set_error_code(t_prompt *_prompt, int _error_code)
{
	char	*errstring;

	errstring = ft_itoa(_error_code);
	env_set_s("?", errstring, SCOPE_LOCAL);
	free(errstring);
	_prompt->error_code = _error_code;
}

void	set_current_path(t_prompt *_prompt, const char *_path)
{
	_prompt->current_path = (char *)_path;
}

void 	prompt_print(t_prompt *_prompt)
{
	ft_dprintf(STDERR, "\e[1;32m%s\e[0m", _prompt->buffer);
}

void	prompt_destroy(t_prompt *_prompt)
{
	free(_prompt->username);
	free(_prompt->hostname);
	free(_prompt->current_path);
	free(_prompt->buffer);
	free(_prompt);
}

int	prompt_update(t_prompt *_prompt)
{
	if (!prompt_update_current_path(_prompt))
		return (0);
	prompt_init_indexes(_prompt);
	prompt_prepare_buffer(_prompt);
	return (1);
}

char	*prompt_read(void)
{
	char	*command_line;

	command_line = NULL;
	if (!(get_next_line(STDIN, &command_line) > 0))
	{
		free(command_line);
		return (NULL);
	}
	return (command_line);
}
