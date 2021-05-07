#ifndef HISTORY_H
# define HISTORY_H

# include "vector.h"

typedef struct s_history
{
	void	*vec;
	int		size;
}			t_history;

t_history	*history_create(void);
void		history_add(t_history *hist, char *cmd);
void		history_destroy(t_history *hist);
void		history_print(t_history *hist);
char		*history_get(t_history *cmd);
#endif
