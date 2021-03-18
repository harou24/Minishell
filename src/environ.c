#include <stdlib.h>
#include <assert.h>

#include "debugger.h"
#include "libft.h"
#include "vector.h"

#include "environ.h"

static void	*g_environ_vec__;

t_bool		environ_init(char **environ)
{
	return (g_environ_vec__
		|| (vector(&g_environ_vec__, V_ADOPT, 0, environ)
		&& vector(&g_environ_vec__, V_PUSHBACK, 0, NULL)));
}

t_bool		environ_deinit()
{
	return (!g_environ_vec__ || vector(&g_environ_vec__, V_DESTROY, TRUE, NULL) == NULL);
}


char		**environ_get()
{
	return (g_environ_vec__ ? (char **)vector(&g_environ_vec__, V_MEM, 0, NULL) : NULL);
}

t_bool		environ_set(size_t index, char *line)
{
	assert(g_environ_vec__);
	assert(line);
	free(vector(&g_environ_vec__, V_POPAT, index, NULL));
	return (vector(&g_environ_vec__, V_PUSHAT, index, line) != NULL);
}

t_bool		environ_add(char *line)
{
	assert(g_environ_vec__);
	assert(line);
	vector(&g_environ_vec__, V_POPBACK, 0, NULL);
	return (vector(&g_environ_vec__, V_PUSHBACK, 0, line) != NULL
			&& vector(&g_environ_vec__, V_PUSHBACK, 0, NULL) != NULL);
}

void		environ_remove(size_t index)
{
	assert(g_environ_vec__);
	vector(&g_environ_vec__, V_POPAT, index, NULL);
}
