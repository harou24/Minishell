#ifndef COMMAND_H
# define COMMAND_H

typedef struct	s_command
{
		int	code_error;
		char	*input;
		char	*output;
		char	*binary_path;
		char	**argv;
		int	argc;
		char	**env;
}		t_command;

t_command	*command_create();
char		*command_get_input();
char		*command_get_output(t_command *_command);
void		command_execute(t_command *_command);
int		command_get_code_error(t_command *_command);
void		command_print_output(t_command *_command);
void		command_destroy(t_command *_command);

#endif
