#include "history.h"
#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

t_history	*history_destroy(t_history **hist)
{
	if (!hist)
		return (NULL);
	if (*hist)
	{
		vector(&(*hist)->vec, V_DESTROY, TRUE, NULL);
		free(*hist);
	}
	return ((*hist = NULL));
}

char	**history_to_array(t_history *hist)
{
	if (hist->size != 0)
		return ((char **)vector(&hist->vec, V_MEM, 0, NULL));
	return (NULL);
}

char	*history_get_next_cmd(t_history *hist)
{
	char	*cmd;

	if (hist->size == 0)
		return (NULL);
	if (hist->current_index >= 0)
	{
		if (hist->current_index > 0)
			hist->current_index--;
		cmd = history_to_array(hist)[hist->current_index];
		return (cmd);
	}
	return (history_get_first(hist));
}

char	*history_get_prev_cmd(t_history *hist)
{
	char	*cmd;

	if (hist->current_index >= 0 && hist->current_index < hist->size)
	{
		if (hist->current_index < hist->size)
			hist->current_index++;
		cmd = history_to_array(hist)[hist->current_index];
	}
	else
		cmd = ft_strdup("");
	return (cmd);
}

void	history_reset_current_index(t_history *hist)
{
	hist->current_index = hist->size;
}
