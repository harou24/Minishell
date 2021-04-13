#include <assert.h>
#include <stdlib.h>

#include "ft_printf.h"
#include "environ.h"
#include "env_singleton.h"
#include "bash_ops.h"

void	dump_scope(t_scope_e scope)
{
	char	**arr;
	size_t	i;

	arr = env_to_array_s(scope);
	i = 0;
	while (arr[i] != NULL)
	{
		ft_printf("%s\n", arr[i]);
		i++;
	}
	ft_array_destroy((void **)arr, ft_array_len((const void **)arr));
}

int	builtin_env(t_command *cmd)
{
	dump_scope(SCOPE_ENVIRON);
	(void)cmd;
	return (0);
}
