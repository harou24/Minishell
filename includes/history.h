#ifndef HISTORY_H
# define HISTORY_H

# include "libft.h"
# include "hashmap.h"

typedef struct s_history
{
	void	*hm;
}		t_history;

t_history	*history_create(void);
void	history_destroy(t_history *history);
t_bool	history_add(t_history *history, char *key, char *value);
char	*history_get(t_history *history, int index);
void	history_print(t_history *history);
#endif
