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
	hist->current_index = hist->size - 1;
}

void	history_destroy(t_history *hist)
{
	vector(&hist->vec, V_DESTROY, TRUE, NULL);
	free(hist);
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
		cmd = history_to_array(hist)[hist->current_index];
		if (hist->current_index > 0)
			hist->current_index--;
		return (cmd);
	}
	return (history_get_first(hist));
}

char	*history_get_prev_cmd(t_history *hist)
{
	char	*cmd;

	if (hist->current_index == hist->size)
		return (NULL);
	if (hist->current_index >= 0 && hist->current_index < hist->size - 1)
	{
		if (hist->current_index < hist->size)
			hist->current_index++;
		cmd = history_to_array(hist)[hist->current_index];
		return (cmd);
	}
	return (history_get_last(hist));
}

void	history_reset_current_index(t_history *hist)
{
	hist->current_index = hist->size - 1;
}
