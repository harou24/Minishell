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

char    *prompt_get_updated_command_line(t_prompt *prompt, char *command_line)
{
    char *first;
    char *second;
    char *new_cmd;

    if (!command_line)
        new_cmd = ft_strdup("");
    else
    {
        first = ft_strsub(command_line, 0, prompt->cursor->pos);
        second = ft_strsub(command_line, prompt->cursor->pos + 1, ft_strlen(command_line));
        new_cmd  = ft_strjoin(first, second);
        free(first);
        free(second);
    }
    return (new_cmd);
}

void    prompt_remove_char(t_prompt *prompt, char *command_line)
{
    if (command_line && cursor_decrease_pos(prompt->cursor))
        termcap_backspace();
}

void    prompt_clean(t_prompt *prompt)
{
    termcap_clean_line();
    prompt_print(prompt);
}

void    prompt_move_cursor_left(t_prompt *prompt)
{
    cursor_move_left(prompt->cursor);
}

void    prompt_move_cursor_right(t_prompt *prompt, char *command_line)
{
    if (command_line)
    {
        cursor_move_right(prompt->cursor);
    }
}

char    *prompt_get_command_from_history(t_prompt *prompt, char *command_line, char *(*history_get)(t_history *hist))
{
    free(command_line);
    command_line = ft_strdup(history_get(prompt->hist));
    if (command_line)
        prompt->cursor->pos = ft_strlen(command_line);
    return (command_line);
}

char    *get_new_cmd(t_prompt *prompt, char *command_line, char *buffer)
{
    char    *first;
    char    *second;
    char    *new_cmd;

    if (!command_line)
        new_cmd = ft_strdup(buffer);
    else
    {
        first = ft_substr(command_line, 0, prompt->cursor->pos - 1);
        first = ft_strjoin(first, buffer);
        second = ft_strsub(command_line, prompt->cursor->pos - 1, ft_strlen(command_line));
        new_cmd = ft_strjoin(first, second);
        free(first);
        free(second);
    }
    return (new_cmd);
}

t_bool    prompt_insert_char(t_prompt *prompt, char c)
{
        if (cursor_increase_pos(prompt->cursor))
        {
            termcap_insert_char(c);
            return (TRUE);
        }
        return (FALSE);
}

char    *command_line_update(t_prompt *prompt, char *command_line, char *buffer)
{
        char *new = get_new_cmd(prompt, command_line, buffer);
        free(command_line);
        command_line = new;
        return (new);
}
void    prompt_manage_history_up(t_prompt *prompt, char *command_line)
{
   command_line = prompt_get_command_from_history(prompt, command_line, history_get_next_cmd);
        prompt_clean(prompt);
        ft_printf("%s", command_line);

}

char *prompt_get_hist(t_prompt *prompt, char *command_line, char *buffer)
{
    if (is_key_arrow_up(buffer) && prompt->hist->size != 0)
    {
        command_line = prompt_get_command_from_history(prompt, command_line, history_get_next_cmd);
        prompt_clean(prompt);
        ft_printf("%s", command_line);
    }
    else if (is_key_arrow_down(buffer) && prompt->hist->size != 0)
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
    return (command_line);
}
char	*handle_key(char *buffer, char *command_line, t_prompt *prompt)
{
    if (is_key_printable(buffer) && prompt_insert_char(prompt, buffer[0]))
            command_line = command_line_update(prompt, command_line, buffer);
    else if (is_key_arrow_up(buffer) || is_key_arrow_down(buffer) )
        command_line = prompt_get_hist(prompt, command_line, buffer);
    else if (is_key_arrow_left(buffer) && command_line)
        prompt_move_cursor_left(prompt);
    else if (is_key_arrow_right(buffer))
        prompt_move_cursor_right(prompt, command_line);
    else if (is_key_backspace(buffer))
    {
        prompt_remove_char(prompt, command_line);
        char *new = prompt_get_updated_command_line(prompt, command_line);
        free(command_line);
        command_line = new;
    }
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
        if (nb_bytes == -1 || buffer[0] == CNTRL_D)
           break ;
        buffer[nb_bytes] = 0;
        if (command_line)
            cursor_set_end(prompt->cursor, ft_strlen(command_line));
        command_line = handle_key(buffer, command_line, prompt);
    }
    while (ft_strcmp(buffer, "\n"));
    history_reset_current_index(prompt->hist);
    cursor_reset(prompt->cursor);
    return (command_line);
}
