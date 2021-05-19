#include "env_access.h"
#include "get_next_line.h"
#include "ft_printf.h"
#include "prompt.h"
#include "termcap.h"
#include "history.h"
#include "key_listener.h"
#include "cursor.h"

char	*prompt_get_command_from_history(t_prompt *prompt,
		char *command_line, char *(*history_get)(t_history *hist))
{
	free(command_line);
	command_line = ft_strdup(history_get(prompt->hist));
	if (command_line)
		prompt->cursor->pos = ft_strlen(command_line);
	return (command_line);
}

char	*get_new_cmd(t_prompt *prompt, char *command_line, char *buffer)
{
	char	*first;
	char	*second;
	char	*new_cmd;

	if (!command_line)
		new_cmd = ft_strdup(buffer);
	else
	{
		first = ft_substr(command_line, 0, prompt->cursor->pos - 1);
		first = ft_strjoin(first, buffer);
		second = ft_strsub(command_line,
				prompt->cursor->pos - 1, ft_strlen(command_line));
		new_cmd = ft_strjoin(first, second);
		free(first);
		free(second);
	}
	return (new_cmd);
}

t_bool	prompt_insert_char(t_prompt *prompt, char c)
{
	if (cursor_increase_pos(prompt->cursor))
	{
		termcap_insert_char(c);
		return (TRUE);
	}
	return (FALSE);
}

char	*command_line_update(t_prompt *prompt, char *command_line, char *buffer)
{
	char	*new;

	new = get_new_cmd(prompt, command_line, buffer);
	free(command_line);
	command_line = new;
	return (new);
}

void	prompt_manage_history_up(t_prompt *prompt, char *command_line)
{
	command_line = prompt_get_command_from_history(prompt,
			command_line, history_get_next_cmd);
	prompt_clean(prompt);
	ft_printf("%s", command_line);
}
