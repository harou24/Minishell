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

/* process_tab.c */
t_bool	p_tab_push(pid_t pid);
pid_t	p_tab_at(size_t index);
size_t	p_tab_size(void);

int		p_tab_waitpid_all(t_waitcond cond);
int		p_tab_signal_all(int signal);

/* process_queue.c */
void	p_queue_register_signalhandler(int sig);
void	p_queue_wait_for_signals(size_t signalcount);

/* process.c */
pid_t	*p_allocate_pid(pid_t pid);

int		p_register_signalhandler(int sig, void (*sighandler)(int sig));
int		p_pause(void);

int		p_waitpid(pid_t pid, t_waitcond cond);
int		p_signal(pid_t pid, int sig);

#endif
