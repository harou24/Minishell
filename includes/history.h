#ifndef HISTORY_H
# define HISTORY_H

# include "vector.h"

typedef struct s_history
{
	void	*vec;
	int		size;
	int		current_index;
}			t_history;

t_history	*history_create(void);
void		history_add(t_history *hist, char *cmd);
char		*history_get_last(t_history *cmd);
char		*history_get_first(t_history *cmd);
char		*history_get_next_cmd(t_history *hist);
char		*history_get_prev_cmd(t_history *hist);
char		**history_to_array(t_history *cmd);
void		history_reset_current_index(t_history *hist);
t_history	*history_destroy(t_history **hist);

#endif
