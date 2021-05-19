#ifndef PROMPT_H
# define PROMPT_H

# include "history.h"
# include "cursor.h"
# include "libft.h"

typedef struct s_prompt
{
	char		*username;
	char		*hostname;
	char		*current_path;
	int			error_code;
	char		*buffer;
	int			error_index;
	int			user_index;
	int			host_index;
	int			path_index;
	int			at_index;
	int			colon_index;
	int			bracket_index;
	t_history	*hist;
	t_cursor	*cursor;
}				t_prompt;

t_prompt	*prompt_create(const char *_username, const char *_hostname);
void		prompt_destroy(t_prompt *_prompt);
char		*prompt_read(t_prompt *prompt);
void		prompt_set_error_code(t_prompt *_prompt, int _error_code);

/* internal functions */
void		prompt_print(t_prompt *_prompt);
int			prompt_update(t_prompt *_prompt);
void		prompt_add_cmd_to_history(t_prompt *prompt, char *cmd);
void		prompt_remove_char(t_prompt *prompt, char *command_line);
void		prompt_clean(t_prompt *prompt);
void		prompt_move_cursor_right(t_prompt *prompt, char *command_line);
void		prompt_move_cursor_left(t_prompt *prompt);
char		*get_new_cmd(t_prompt *prompt, char *command_line, char *buffer);
t_bool		prompt_insert_char(t_prompt *prompt, char c);
char		*command_line_update(t_prompt *prompt,
				char *command_line,
				char *buffer);
void		prompt_manage_history_up(t_prompt *prompt, char *command_line);
char		*prompt_get_hist(t_prompt *prompt,
				char *command_line, char *buffer);
char		*cmd_update_char_removal(t_prompt *prompt, char *command_line);
char		*handle_key(char *buffer, char *command_line, t_prompt *prompt);
void		prompt_add_cmd_to_history(t_prompt *prompt, char *cmd);
char		*prompt_get_command_from_history(t_prompt *prompt, char *cmd_line,
				char*(*history_get)(t_history *hist));
char		*prompt_get_updated_command_line(t_prompt *prompt,
				char *command_line);
#endif
