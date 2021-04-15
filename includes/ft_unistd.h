/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unistd.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:09:47 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:09:48 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UNISTD_H
# define FT_UNISTD_H

# define		PIPE_READ	0
# define		PIPE_WRITE	1

int				ft_pipe(int pipefd[2]);
int				drop_pipe(int pipefd[2]);

char			*ft_gethostname(void);
char			*ft_realpath(const char *path);

#endif
