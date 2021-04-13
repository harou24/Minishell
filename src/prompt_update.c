#include "filesystem_traversal.h"
#include "get_next_line.h"
#include "ft_printf.h"
#include "prompt.h"

#define __PROMPT_MAX_LENGTH 1024                                 
#define __ERROR_LENGTH 4

static void	prompt_init_indexes(t_prompt *_prompt)
{
	_prompt->error_index = 0;
	_prompt->user_index = 3;
	_prompt->at_index = _prompt->user_index + ft_strlen(_prompt->username);
	_prompt->host_index = _prompt->at_index + 1;
	_prompt->colon_index = _prompt->host_index + ft_strlen(_prompt->hostname);
	_prompt->path_index = _prompt->colon_index + 1;
	_prompt->bracket_index = _prompt->path_index + ft_strlen(
			_prompt->current_path);
}

static void	prompt_prepare_buffer(t_prompt *_prompt)
{
	prompt_init_indexes(_prompt);
	ft_snprintf(_prompt->buffer, __ERROR_LENGTH, "%-*d",
		__ERROR_LENGTH, _prompt->error_code);
	ft_snprintf(_prompt->buffer + _prompt->user_index,
		ft_strlen(_prompt->username) + 1, "%s", _prompt->username);
	ft_snprintf(_prompt->buffer + _prompt->at_index, 2, "@");
	ft_snprintf(_prompt->buffer + _prompt->host_index,
		ft_strlen(_prompt->hostname) + 1, "%s", _prompt->hostname);
	ft_snprintf(_prompt->buffer + _prompt->colon_index, 2, ":");
	ft_snprintf(_prompt->buffer + _prompt->path_index,
		ft_strlen(_prompt->current_path) + 1, "%s", _prompt->current_path);
	ft_snprintf(_prompt->buffer + _prompt->bracket_index, 3, "> ");
}

static int	prompt_update_current_path(t_prompt *_prompt)
{
	free(_prompt->current_path);
	_prompt->current_path = fs_get_cur_dir_name();
	if (!_prompt->current_path)
		return (0);
	return (1);
}

int	prompt_update(t_prompt *_prompt)
{
	if (!prompt_update_current_path(_prompt))
		return (0);
	prompt_prepare_buffer(_prompt);
	return (1);
}
