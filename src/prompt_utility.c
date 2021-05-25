#include "env_access.h"
#include "get_next_line.h"
#include "ft_printf.h"
#include "prompt.h"
#include "termcap.h"
#include "history.h"
#include "key_listener.h"
#include "cursor.h"

static char	*__adjustedbuffer(t_prompt *_prompt)
{
	if (_prompt->error_code == 0)
		return (&_prompt->buffer[_prompt->user_index]);
	else
		return (&_prompt->buffer[_prompt->error_index]);
}

const char	*prompt_ps1(t_prompt *_prompt)
{
	if (_prompt->error_code == 0)
		return ("\e[0;32m%s\e[0m");
	else
		return ("\e[0;91m%s\e[0m");
}

void 	prompt_print(t_prompt *_prompt)
{
	ft_dprintf(STDERR, prompt_ps1(_prompt), __adjustedbuffer(_prompt));
}

void	prompt_set_error_code(t_prompt *_prompt, int _error_code)
{
	env_set_lasterror(_error_code);
	_prompt->error_code = _error_code;
}

char	*prompt_read(t_prompt *prompt)
{
	char		*command_line;
	t_termcap	term;
	char		buffer[15];
	int			nb_bytes;

	termcap_init(&term);
	command_line = NULL;
	while (ft_strcmp(buffer, "\n"))
	{
		nb_bytes = read(STDIN, buffer, 15);
		if (nb_bytes == -1 || buffer[0] == CNTRL_D)
		{
			prompt_clean(prompt);
			break ;
		}
		buffer[nb_bytes] = 0;
		if (command_line)
			cursor_set_end(prompt->cursor, ft_strlen(command_line));
		command_line = handle_key(buffer, command_line, prompt);
	}
	history_reset_current_index(prompt->hist);
	cursor_reset(prompt->cursor);
	termcap_deinit(&term);
	return (command_line);
}
