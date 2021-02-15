#ifndef PROMPT_H
# define PROMPT_H

#include "libft.h"
#include "directory.h"
#include <stdlib.h>

#define BUFFER_SIZE 255

typedef struct	s_prompt
{
		char 	*username;
		char 	*hostname;
		char 	*current_path;
		int	error_code;
		char 	*buffer;
}		t_prompt;

t_prompt	*prompt_create(const char *_username, const char *_hostname);
void		prompt_init_buffer(t_prompt *_prompt);
void		prompt_update_path(t_prompt *_prompt);
void		prompt_set_current_path(const char *_path);
void 		prompt_set_error_code(int _error_code);
void		prompt_print(t_prompt *_prompt);
void		prompt_destroy(t_prompt *_prompt);

#endif
