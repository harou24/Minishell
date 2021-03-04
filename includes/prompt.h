#ifndef PROMPT_H
# define PROMPT_H

typedef struct	s_prompt
{
		char 	*username;
		char 	*hostname;
		char 	*current_path;
		int	error_code;
		char 	*buffer;
		int	error_index;
		int	user_index;
		int	host_index;
		int 	path_index;
		int	at_index;
		int	colon_index;
		int 	bracket_index;
}		t_prompt;

t_prompt	*prompt_create(const char *_username, const char *_hostname);
void		prompt_prepare_buffer(t_prompt *_prompt);
void		prompt_init_indexes(t_prompt *_prompt);
void		prompt_update_current_path(t_prompt *_prompt);
void		prompt_set_current_path(const char *_path);
void 		prompt_set_error_code(t_prompt *_prompt, int _error_code);
void		prompt_print(t_prompt *_prompt);
void		prompt_destroy(t_prompt *_prompt);
void		prompt_update(t_prompt *_prompt);
char		*prompt_read(void);

#endif
