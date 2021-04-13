/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:10:04 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:10:05 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef enum e_shellerr
{
	SHELL_OK,
	SHELL_EXISTS,
	SHELL_ERRNO,
	SHELL_EXITED
}					t_shellerr;

t_shellerr			shell_interactive(char **env);

t_shellerr			shell_init(char **env);
void				shell_deinit(void);

int					shell_exec(const char *command_string);

#endif
