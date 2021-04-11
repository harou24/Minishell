#include "get_next_line.h"
#include "ft_printf.h"
#include "prompt.h"

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
