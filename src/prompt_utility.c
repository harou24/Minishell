#include "env_access.h"
#include "get_next_line.h"
#include "ft_printf.h"
#include "prompt.h"

#define __NB_BYTES 100
#define __BUFFER_SIZE 2000

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

char	*prompt_read(void)
{
	char	*command_line;
	int		nb_bytes;
	char	buff[__BUFFER_SIZE];

	command_line = NULL;
	do
	{
		nb_bytes = read(STDIN, buff, __NB_BYTES);
		buff[nb_bytes] = 0;
	}
	while(!ft_strcmp(buff,"\n"));
	command_line = ft_strdup(buff);
	return (command_line);
}
