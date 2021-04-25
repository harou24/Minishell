#include <assert.h>

#include "get_next_line.h"
#include "filesystem_traversal.h"
#include "ft_printf.h"
#include "prompt.h"

#define __PROMPT_BUFF_SIZE 255

void	prompt_destroy(t_prompt *_prompt)
{
	free(_prompt->username);
	free(_prompt->hostname);
	free(_prompt->current_path);
	free(_prompt->buffer);
	free(_prompt);
}

t_prompt 	*prompt_create(const char *username, const char *hostname)
{
	t_prompt	*prompt;

	if (!username)
		username = "NOBODY";
	if (!hostname)
		username = "LOCALHOST";
	prompt = ft_calloc(sizeof(t_prompt), 1);
	if (!prompt)
		return (NULL);
	prompt->username = ft_strdup(username);
	prompt->hostname = ft_strdup(hostname);
	prompt->error_code = 0;
	prompt->buffer = ft_calloc(sizeof(char), __PROMPT_BUFF_SIZE);
	prompt->current_path = fs_get_cur_dir_name();
	if (!prompt->current_path || !prompt->buffer
		|| !prompt->username || !prompt->hostname)
	{
		prompt_destroy(prompt);
		return (NULL);
	}
	prompt_update(prompt);
	return (prompt);
}
