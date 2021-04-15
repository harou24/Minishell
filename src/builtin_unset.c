#include "bash_ops.h"
#include "env_singleton.h"
#include "ft_printf.h"

int	builtin_unset(t_command *cmd)
{
	const size_t	argc = argv_get_size(cmd->argv);
	const char		**argv = argv_get_array(cmd->argv);
	size_t			i;

	if (argc < 2)
	{
		ft_dprintf(STDERR, "unset: not enough arguments");
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		if (!env_unset_s(argv[i]))
			return (1);
		i++;
	}
	return (0);
}
