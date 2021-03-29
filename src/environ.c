#include <stdlib.h>
#include <assert.h>

#include "debugger.h"
#include "libft.h"
#include "vector.h"

#include "environ.h"

static void	*g_environ_vec__;

t_bool		environ_init(char **environ)
{
	assert(environ);
	return (g_environ_vec__ != NULL
		|| vector(&g_environ_vec__, V_ADOPT, ft_arraylen((const void **)environ) + 1, environ));
}

t_bool		environ_deinit()
{
	return (!g_environ_vec__ || vector(&g_environ_vec__, V_DESTROY, TRUE, NULL) == NULL);
}

char		**environ_get()
{
	assert(g_environ_vec__);
	return (g_environ_vec__ ? (char **)vector(&g_environ_vec__, V_MEM, 0, NULL) : NULL);
}

t_bool		environ_set(size_t index, char *line)
{
	assert(g_environ_vec__);
	assert(line);
	assert(index < environ_size());
	dbg("adding line '%s' to environ @ index %zu!\n", line, index);
	return (vector(&g_environ_vec__, V_REPLACE, index, line) != NULL);
}

t_bool		environ_add(char *line)
{
	assert(g_environ_vec__);
	assert(line);
	dbg("adding line '%s' to environ!\n", line);
	assert(vector(&g_environ_vec__, V_POPBACK, 0, NULL) == NULL);
	return (vector(&g_environ_vec__, V_PUSHBACK, 0, line) != NULL
			&& vector(&g_environ_vec__, V_PUSHBACK, 0, NULL) != NULL);
}

size_t		environ_size()
{
	assert(g_environ_vec__);
	assert (*(size_t *)vector(&g_environ_vec__, V_SIZE, 0, NULL) > 0);
	return (*(size_t *)vector(&g_environ_vec__, V_SIZE, 0, NULL) - 1);
}

void		environ_remove(size_t index)
{
	assert(g_environ_vec__);
	vector(&g_environ_vec__, V_POPAT, index, NULL);
}
