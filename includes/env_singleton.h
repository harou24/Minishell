#ifndef ENV_SINGLETON_H
# define ENV_SINGLETON_H

# include "libft.h"
# include "env.h"

t_env	*env_init(char **env);
void	env_deinit(t_env **env);

char	*env_get_s(const char *key);
t_bool	env_set_s(const char *key, char *value, e_scope scope);
t_bool	env_set_s_line(const char *line, e_scope scope);
t_bool	env_unset_s(const char *key);

char	**env_to_array_s(e_scope scope);

#endif
