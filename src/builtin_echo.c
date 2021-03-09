#include "bash_ops.h"
#include "ft_printf.h"
#include "libft.h"

#define N_FLAG_POS 1

static t_bool	is_n_flag(t_command *cmd)
{
	if (cmd->argv->argc > N_FLAG_POS && ft_strcmp(cmd->argv->argv[N_FLAG_POS], "-n") == 0)
		return (TRUE);
	return (FALSE);
}

static	void print_output(t_command *cmd)
{
	int	count;
	t_bool	_is_n_flag;

	count = 1;
	_is_n_flag = is_n_flag(cmd);
	if (_is_n_flag)
		count++;
	while (count < cmd->argv->argc)
	{
		ft_dprintf(cmd->fds[FD_OUT], "%s", argv_get(cmd->argv, count));
		if (count != cmd->argv->argc - 1)
			ft_dprintf(cmd->fds[FD_OUT], " ");
		count++;
	}
	if (!_is_n_flag)
		ft_dprintf(cmd->fds[FD_OUT], "\n");
}

int	builtin_echo(t_command *cmd)
{
	print_output(cmd);
	return (0);
}
