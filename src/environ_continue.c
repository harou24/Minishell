#include <stdlib.h>

#include "vector.h"

#include "environ.h"

extern void	*g_environ_vec__;

size_t	environ_size(void)
{
	return (*(size_t *)vector(&g_environ_vec__, V_SIZE, 0, NULL) - 1);
}

void	environ_remove(size_t index)
{
	free(vector(&g_environ_vec__, V_POPAT, index, NULL));
}
