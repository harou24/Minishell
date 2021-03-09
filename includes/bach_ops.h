#ifndef BACH_OPS
# define BACH_OPS

int	builtin_echo(t_command *cmd, t_env *env);
int	builtin_exit(t_command *cmd);
int 	builtin_set_env(t_command *cmd, t_env *env);
int	builtin_unset_env(t_command *cmd, t_env *env);
int	builtin_export(t_command *cmd);
int	builtin_cd(t_command *cmd);
int	builtin_pwd(t_command *cmd);

#endif
