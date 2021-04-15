/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bash_ops.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:08:51 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:08:53 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASH_OPS_H
# define BASH_OPS_H

# include "libft.h"
# include "command.h"

int		builtin_echo(t_command *cmd);
int		builtin_exit(t_command *cmd);
int		builtin_unset(t_command *cmd);
int		builtin_export(t_command *cmd);
int		builtin_pwd(t_command *cmd);
int		builtin_env(t_command *cmd);
int		builtin_cd(t_command *cmd);

int		op_execbin(t_command *cmd);
int		op_assignment(t_command *cmd);

#endif
