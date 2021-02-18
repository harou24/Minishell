#ifndef SHELL_H
# define SHELL_H

typedef struct 	s_shell {
		char		*input;
		char		**env;
		t_command	*commands;
		int		nb_command;
}		t_shell;

t_shell	*shell_create(void);
char	**shell_get_env(int _argc, char **_argv, char **_env);
int	shell_read_input(void);
int	shell_init_commands(t_shell *_shell);
void	shell_destroy(t_shell *shell);

#endif
