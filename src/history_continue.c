#include "history.h"
#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

t_history	*history_create(void)
{
	const size_t	vec_size = 100;
	t_history		*hist;

	hist = (t_history *)malloc(sizeof(t_history));
	if (!hist || !vector(&hist->vec, V_CREATE, vec_size, NULL))
	{
		free(hist);
		return (NULL);
	}
	hist->size = 0;
	hist->current_index = 0;
	return (hist);
}

char	*history_get_last(t_history *hist)
{
	if (hist->size == 0)
		return (NULL);
	return ((char *)vector(&hist->vec, V_PEEKBACK, 0, NULL));
}

char	*history_get_first(t_history *hist)
{
	return ((char *)vector(&hist->vec, V_PEEKFRONT, 0, NULL));
}

void	history_add(t_history *hist, char *cmd)
{
	if (hist->size != 0 && !ft_strcmp(history_get_last(hist), cmd))
		return ;
	vector(&hist->vec, V_PUSHBACK, 0, cmd);
	hist->size++;
	hist->current_index = hist->size;
}
