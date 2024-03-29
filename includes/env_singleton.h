/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_singleton.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:09:26 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:09:27 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_SINGLETON_H
# define ENV_SINGLETON_H

# include "libft.h"
# include "env.h"

t_env	*env_init(char **env);
void	env_deinit(t_env **env);

char	*env_get_s(const char *key);
t_bool	env_set_s(const char *key, char *value, t_scope_e scope);
t_bool	env_set_s_line(const char *line, t_scope_e scope);
t_bool	env_unset_s(const char *key);

char	**env_to_array_s(t_scope_e scope);

#endif
