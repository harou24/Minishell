#include "env_access.h"
#include "get_next_line.h"
#include "ft_printf.h"
#include "prompt.h"
#include "termcap.h"
#include "history.h"
#include "key_listener.h"
#include "cursor.h"

char	*prompt_get_updated_command_line(t_prompt *prompt, char *command_line)
{
	char	*first;
	char	*second;
	char	*new_cmd;

	if (!command_line)
		new_cmd = ft_strdup("");
	else
	{
		first = ft_strsub(command_line, 0, prompt->cursor->pos);
		second = ft_strsub(command_line,
				prompt->cursor->pos + 1,
				ft_strlen(command_line));
		new_cmd = ft_strjoin(first, second);
		free(first);
		free(second);
	}
	return (new_cmd);
}

void	prompt_remove_char(t_prompt *prompt, char *command_line)
{
	if (command_line && cursor_decrease_pos(prompt->cursor))
		termcap_backspace();
}

void	prompt_clean(t_prompt *prompt)
{
	termcap_clean_line();
	prompt_print(prompt);
}

void	prompt_move_cursor_left(t_prompt *prompt)
{
	cursor_move_left(prompt->cursor);
}

void	prompt_move_cursor_right(t_prompt *prompt, char *command_line)
{
	if (command_line)
	{
		cursor_move_right(prompt->cursor);
	}
}
