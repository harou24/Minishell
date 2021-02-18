#ifndef COMMAND_H
# define COMMAND_H

typedef struct	s_command
{
		char	*input;
		int	code_error;
		char	**argv;
		int	argc;
		char	**env;
		int	is_built_int;
}		t_command;

t_command	*command_create();
int		command_read_input(t_command *_command);
char		*command_get_input(t_command *_command);
char		**get_environment();
void		command_execute(t_command *_command);
int		command_get_code_error(t_command *_command);
void		command_destroy(t_command *_command);

#endif
