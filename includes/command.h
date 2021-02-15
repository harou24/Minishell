#ifndef COMMAND_H
# define COMMAND_H

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

typedef struct	s_command
{
		int	code_error;
		char	*input;
		char	*output;
}		t_command;

t_command	*command_create(const char *_input);
int		command_execute(t_command *_command);
int		command_get_code_error(t_command *_command);
void		command_print_output(t_command *_command);
void		command_destroy(t_command *_command);

#endif
