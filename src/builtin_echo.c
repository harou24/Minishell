#include "bash_ops.h"
#include "ft_printf.h"
#include "libft.h"

#define N_FLAG_POS 1

static t_bool	check_has_n_flag(t_argv *argv)
{
	return (argv->argc > N_FLAG_POS
		&& ft_strcmp(argv->argv[N_FLAG_POS], "-n") == 0);
}

static void	print_for_argv(t_argv *argv)
{
	int		index;
	t_bool	has_n_flag;

	index = 1;
	has_n_flag = check_has_n_flag(argv);
	if (has_n_flag)
		index++;
	while (index < argv->argc)
	{
		ft_printf("%s", argv_get(argv, index));
		if (index != argv->argc - 1)
			ft_printf(" ");
		index++;
	}
	if (!has_n_flag)
		ft_printf("\n");
}

int	builtin_echo(t_command *cmd)
{
	print_for_argv(cmd->argv);
	return (0);
}
