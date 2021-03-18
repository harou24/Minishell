#include "bash_ops.h"
#include "env_access.h"
#include "ft_printf.h"
#include "filesystem_traversal.h"

int	builtin_pwd(t_command *cmd)
{
	char	*pwd;
	(void)cmd;

	pwd = fs_get_cur_dir_name();
	if (!pwd)
		exit (EXIT_FAILURE);
	ft_dprintf(STDOUT, "%s\n", pwd);
	exit(EXIT_SUCCESS);
}
