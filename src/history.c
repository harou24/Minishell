#include "history.h"
#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

t_history *history_create(void)
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
	return (hist);
}

void	history_add(t_history *hist, char *cmd)
{
	vector(&hist->vec, V_PUSHBACK, 0, cmd);
	hist->size++;
}

void	history_print(t_history *hist)
{
	char	*cmd;
	int 	i;

	i = 0;
	while (i < hist->size)
	{
		cmd = (char *)vector(&hist->vec, V_PEEKAT, i, NULL);
		ft_printf("%s\n", cmd);
	}
}

char	*history_get(t_history *hist)
{
	return ((char *)vector(&hist->vec, V_PEEKBACK, 0, NULL));

}
void t_history_destroy(t_history *hist)
{
	vector(&hist->vec, V_DESTROY, TRUE, NULL);
	free(hist);
}
