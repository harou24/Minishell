#include <stdlib.h>

#include "debugger.h"
#include "libft.h"
#include "vector.h"

#include "environ.h"

void	*g_environ_vec__ = NULL;

t_bool	environ_init(char **environ)
{
	return (g_environ_vec__ != NULL
		|| vector(&g_environ_vec__, V_ADOPT,
			ft_array_len((const void **)environ) + 1, environ));
}

t_bool	environ_deinit(void)
{
	return (!g_environ_vec__
		|| vector(&g_environ_vec__, V_DESTROY, TRUE, NULL) == NULL);
}
