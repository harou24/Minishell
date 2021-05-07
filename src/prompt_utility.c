#include "env_access.h"
#include "get_next_line.h"
#include "ft_printf.h"
#include "prompt.h"
#include "termcap.h"

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

char	*handle_buffer(char *buffer, char *command_line)
{
	if (ft_isprint(buffer[0]))
	{
		command_line = ft_strjoin(command_line, buffer);
		write(1, buffer, 1);
	}
	else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 65)
	{	
		ft_printf("arrow_up\n");
	}
	else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 66)
	{	
		ft_printf("arrow_down\n");
	}
	else if (buffer[0] == 127)
	{
		if (command_line && ft_strlen(command_line) > 0)
		{
			termcap_backspace();
			command_line[ft_strlen(command_line) - 1] = '\0';
		}
	}
	else if (buffer[0] == '\n')
		write(1, "\n", 1);
	return command_line;
}

char	*prompt_read(void)
{
	char	*command_line;
	t_termcap	term;
	char	buffer[15];
	int		nb_bytes;
	
	termcap_init(&term);
	command_line = NULL;
	do
	{
		nb_bytes = read(STDIN, buffer, 15);
		buffer[nb_bytes] = 0;
		command_line = handle_buffer(buffer, command_line);
	}
	while (ft_strcmp(buffer, "\n"));
	return (command_line);
}
