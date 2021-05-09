#ifndef PROMPT_H
# define PROMPT_H

# include "history.h"

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
    int         cursor_pos;
}				t_prompt;

t_prompt	*prompt_create(const char *_username, const char *_hostname);
void		prompt_destroy(t_prompt *_prompt);
char		*prompt_read(t_prompt *prompt);
void		prompt_set_error_code(t_prompt *_prompt, int _error_code);

/* internal functions */
void		prompt_print(t_prompt *_prompt);
int			prompt_update(t_prompt *_prompt);
void		prompt_add_cmd_to_history(t_prompt *prompt, char *cmd);

#endif
