#include "env_access.h"
#include "get_next_line.h"
#include "ft_printf.h"
#include "prompt.h"
#include "termcap.h"
#include "history.h"
#include "key_listener.h"
#include "cursor.h"

char	*prompt_get_hist(t_prompt *prompt, char *command_line, char *buffer)
{
	if (is_key_arrow_up(buffer) && prompt->hist->size != 0)
	{
		command_line = prompt_get_command_from_history(prompt,
				command_line, history_get_next_cmd);
		prompt_clean(prompt);
		ft_printf("%s", command_line);
	}
	else if (is_key_arrow_down(buffer) && prompt->hist->size != 0)
	{	
		if (prompt->hist->current_index != prompt->hist->size - 1)
		{
			command_line = prompt_get_command_from_history(prompt,
					command_line, history_get_prev_cmd);
			prompt_clean(prompt);
			ft_printf("%s", command_line);
		}
		else
		{
			free(command_line);
			command_line = ft_strdup("");
			prompt_clean(prompt);
			cursor_reset(prompt->cursor);
			history_reset_current_index(prompt->hist);
		}
	}
	return (command_line);
}

char	*cmd_update_char_removal(t_prompt *prompt, char *command_line)
{
	char	*new;

	prompt_remove_char(prompt, command_line);
	new = prompt_get_updated_command_line(prompt, command_line);
	free(command_line);
	command_line = new;
	return (command_line);
}

char	*handle_key(char *buffer, char *command_line, t_prompt *prompt)
{
	if (is_key_printable(buffer) && prompt_insert_char(prompt, buffer[0]))
		command_line = command_line_update(prompt, command_line, buffer);
	else if (is_key_arrow_up(buffer) || is_key_arrow_down(buffer))
		command_line = prompt_get_hist(prompt, command_line, buffer);
	else if (is_key_arrow_left(buffer) && command_line)
		prompt_move_cursor_left(prompt);
	else if (is_key_arrow_right(buffer))
		prompt_move_cursor_right(prompt, command_line);
	else if (is_key_backspace(buffer))
		command_line = cmd_update_char_removal(prompt, command_line);
	else if (buffer[0] == CNTRL_U)
	{
		free(command_line);
		command_line = ft_strdup("");
		prompt_clean(prompt);
		cursor_reset(prompt->cursor);
	}
	if (is_key_new_line(buffer))
	{
		if (!command_line || !ft_strlen(command_line))
			command_line = ft_strdup("");
		write(1, "\n", 1);
	}
	return (command_line);
}

void	prompt_add_cmd_to_history(t_prompt *prompt, char *cmd)
{
	history_add(prompt->hist, cmd);
}
