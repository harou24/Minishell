#include "env_access.h"
#include "get_next_line.h"
#include "ft_printf.h"
#include "prompt.h"

void 	prompt_print(t_prompt *_prompt)
{
	ft_dprintf(STDERR, "\e[1;32m%s\e[0m", _prompt->buffer);
}

void	prompt_set_error_code(t_prompt *_prompt, int _error_code)
{
	env_set_lasterror(_error_code);
	_prompt->error_code = _error_code;
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
