/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:10:17 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:10:18 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

# include <sys/types.h>

# include <signal.h>
# include <unistd.h>

# include "libft.h"

/* this needs a whole lot more love */

typedef enum e_waitcond
{
	W_EXITED,
	W_TERMINATED,
	W_ABORTED
}				t_waitcond;

/* process.c */
pid_t	*p_allocate_pid(pid_t pid);

int		p_register_signalhandler(int sig, void (*sighandler)(int sig));

int		p_wait(pid_t *pid, t_waitcond cond);
int		p_signal(pid_t pid, int sig);

#endif
