#ifndef COMMAND_H
# define COMMAND_H

typedef struct	s_command
{
		char	*input;
		char	*output;
		int	code_error;
		char	**argv;
		int	argc;
		char	**env;
}		t_command;

t_command	*command_create();
int		command_read_input(t_command *_command);
char		*command_get_input(t_command *_command);
char		*command_get_output(t_command *_command);
void		command_execute(t_command *_command);
int		command_get_code_error(t_command *_command);
void		command_print_output(t_command *_command);
void		command_destroy(t_command *_command);

#endif
