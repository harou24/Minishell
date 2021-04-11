#include <stdlib.h>

#include "debugger.h"
#include "libft.h"
#include "vector.h"

#include "environ.h"

void	*g_environ_vec__;

t_bool	environ_init(char **environ)
{
	return (g_environ_vec__ != NULL
		|| vector(&g_environ_vec__, V_ADOPT,
			ft_arraylen((const void **)environ) + 1, environ));
}

t_bool	environ_deinit(void)
{
	return (!g_environ_vec__
		|| vector(&g_environ_vec__, V_DESTROY, TRUE, NULL) == NULL);
}

char	**environ_get(void)
{
	if (g_environ_vec__)
		return ((char **)vector(&g_environ_vec__, V_MEM, 0, NULL));
	return (NULL);
}

t_bool	environ_set(size_t index, char *line)
{
	return (vector(&g_environ_vec__, V_REPLACE, index, line) != NULL);
}

t_bool	environ_add(char *line)
{
	vector(&g_environ_vec__, V_REPLACE, environ_size(), line);
	vector(&g_environ_vec__, V_PUSHBACK, 0, NULL);
	return (TRUE);
}
