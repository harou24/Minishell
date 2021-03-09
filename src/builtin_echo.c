#include "bash_ops.h"
#include "env_singleton.h"
#include "ft_printf.h"
#include "libft.h"

int	is_n_flag(t_command *cmd)
{
	if (ft_strcmp(cmd->argv->argv[1], "-n") == 0)
		return 1;
	return (0);
}

int	builtin_echo(t_command *cmd)
{
	int	count;

	if (is_n_flag(cmd))
		count = 2;
	else
		count = 1;
	while (count < cmd->argv->argc)
	{
		ft_dprintf(STDERR, "%s", cmd->argv->argv[count]);
		if (count != cmd->argv->argc - 1)
			ft_dprintf(STDERR, " ");
		if (!is_n_flag(cmd))
			ft_dprintf(STDERR, "\n");
		count++;
	}
	return (1);
}
