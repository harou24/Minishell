#ifndef COMMAND_H
# define COMMAND_H

typedef struct	s_command
{
		char	*input;
		int	code_error;
		char	**argv;
		int	argc;
}		t_command;

t_command	*command_create(const char *_input);
void		command_execute(t_command *_command);
int		command_get_code_error(t_command *_command);
void		command_destroy(t_command *_command);

/*builtins*/

int		command_run_builtins(t_command *_command);
int		command_run_echo(t_command *_command);
int		command_run_cd(t_command *_command);
int		command_run_pwd(t_command *_command);
int		command_run_unset(t_command *_command);
int		command_run_export(t_command *_command);
int		command_run_env(t_command *_command);
int		command_run_exit(t_command *_command);

#endif
