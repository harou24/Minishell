#include "env_access.h"
#include "get_next_line.h"
#include "ft_printf.h"
#include "prompt.h"
#include "termcap.h"
#include "history.h"

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

void    prompt_remove_char(char *command_line)
{
	if (command_line && ft_strlen(command_line) > 0)
    {
	    termcap_backspace();
	    command_line[ft_strlen(command_line) - 1] = '\0';
    }
}

void    prompt_clean(t_prompt *prompt)
{
	termcap_clean_line();
	prompt_print(prompt);
}

char    *prompt_get_command_from_history(t_prompt *prompt, char *command_line, char *(*history_get)(t_history *hist))
{
	free(command_line);
	command_line = ft_strdup(history_get(prompt->hist));
    return (command_line);
}

char	*handle_key(char *buffer, char *command_line, t_prompt *prompt)
{
	if (termcap_is_key_printable(buffer))
	{
		command_line = ft_strjoin(command_line, buffer);
		write(1, buffer, 1);
	}
	else if (termcap_is_key_arrow_up(buffer) && prompt->hist->size != 0)
	{
		command_line = prompt_get_command_from_history(prompt, command_line, history_get_next_cmd);
		prompt_clean(prompt);
        ft_printf("%s", command_line);
	}
	else if (termcap_is_key_arrow_down(buffer) && prompt->hist->size != 0)
	{	
        if (prompt->hist->current_index != prompt->hist->size - 1)
        {
            command_line = prompt_get_command_from_history(prompt, command_line, history_get_prev_cmd);
		    prompt_clean(prompt);
            ft_printf("%s", command_line);
        }
        else
        {
            free(command_line);
            command_line = ft_strdup("");
		    prompt_clean(prompt);
        }
	}
	else if (termcap_is_key_arrow_left(buffer))
	    termcap_move_left();
    else if (termcap_is_key_arrow_right(buffer))
	    termcap_move_right();
    else if (termcap_is_key_backspace(buffer))
            prompt_remove_char(command_line);
	if (termcap_is_key_new_line(buffer))
	{
		if (!command_line || !ft_strlen(command_line))
			command_line = ft_strdup("");
		write(1, "\n", 1);
		history_reset_current_index(prompt->hist);
	}
	return (command_line);
}

void	prompt_add_cmd_to_history(t_prompt *prompt, char *cmd)
{
	history_add(prompt->hist, cmd);
}

char	*prompt_read(t_prompt *prompt)
{
	char		*command_line;
	t_termcap	term;
	char		buffer[15];
	int			nb_bytes;
	
	termcap_init(&term);
	command_line = NULL;
	do
	{
		nb_bytes = read(STDIN, buffer, 15);
		buffer[nb_bytes] = 0;
		command_line = handle_key(buffer, command_line, prompt);
	}
	while (ft_strcmp(buffer, "\n"));
	return (command_line);
}
