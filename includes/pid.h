#ifndef PID_H
# define PID_H

#include <sys/types.h>
#include <unistd.h>

#include "libft.h"

pid_t	*pid_allocate(pid_t pid);

t_bool	pid_push(pid_t pid);
pid_t	pid_last();

int		pid_wait(pid_t pid);
int		pid_kill(pid_t pid);

int		pid_wait_all();
int		pid_kill_all(); /* wouldn't kill_all_children be a better name ? :p */

#endif
