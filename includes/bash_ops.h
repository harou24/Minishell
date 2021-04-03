#ifndef BASH_OPS
# define BASH_OPS

# include "libft.h"
# include "command.h"

int	builtin_echo(t_command *cmd);
int	builtin_exit(t_command *cmd);
int	builtin_unset(t_command *cmd);
int	builtin_export(t_command *cmd);
int	builtin_pwd(t_command *cmd);
int	builtin_env(t_command *cmd);

int	exec_bin(t_command *cmd);
int	op_assignment(t_command *cmd);

int	builtin_cd(t_command *cmd);

char	*ft_realpath(char *path);

int 	__go_to_prev_dir();
int	__go_to_home();
int	__go_to_path(const char *path);
void	__print_cur_path();

t_bool	__update_dir_change(char *new_path);
t_bool	__is_tilde(const char *str);
t_bool	__is_dash(const char *str);
t_bool __is_path_in_cdpath(const char *path);
t_bool	__is_print_path_needed(const char *path);


#endif
