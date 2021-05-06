#include "history.h"
#include <stdlib.h>
#include "ft_printf.h"

#define __HISTORY_SIZE 1024

t_history *history_create(void)
{
	t_history	*history;

	history = (t_history *)malloc(sizeof(t_history));
	if (!history)
		return (NULL);
	history->hm = hm_new(__HISTORY_SIZE);
	if(!history->hm)
	{
		history_destroy(history);
		return (NULL);
	}
	return (history);
}

t_bool	history_add(t_history *history, char *key, char *value)
{
	if (!hm_set(history->hm, key, value))
		return (FALSE);
	return (TRUE);
}

char	*history_get(t_history *history, int index)
{
	return ((char *)hm_get(history->hm, ft_itoa(index)));
}

void	history_print(t_history *history)
{
	char	*value;
	int i =0;
	while ((value = history_get(history, i)))
	{
		ft_printf("%s\n", value);
		i++;
	}
}

void	history_destroy(t_history *history)
{
	hm_destroy(history->hm, free);
	free(history);
}
