#include "bash_ops.h"
#include "ft_printf.h"
#include "libft.h"

#define N_FLAG_POS 1

static t_bool	check_has_n_flag(size_t argc, const char **argv)
{
	return (argc > N_FLAG_POS
		&& ft_strcmp(argv[N_FLAG_POS], "-n") == 0);
}

static void	print_for_argv(size_t argc, const char **argv)
{
	size_t	index;
	t_bool	has_n_flag;

	index = 1;
	has_n_flag = check_has_n_flag(argc, argv);
	if (has_n_flag)
		index++;
	while (index < argc)
	{
		if (ft_strlen(argv[index]) > 0)
		{
			ft_printf("%s", argv[index]);
			if (index != argc - 1)
				ft_printf(" ");
		}
		index++;
	}
	if (!has_n_flag)
		ft_printf("\n");
}

int	builtin_echo(t_command *cmd)
{
	print_for_argv(argv_get_size(cmd->argv), argv_get_array(cmd->argv));
	return (0);
}
