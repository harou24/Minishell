#include "bash_ops.h"
#include "env_access.h"
#include "ft_printf.h"
#include "filesystem_traversal.h"

int	builtin_pwd(t_command *cmd)
{
	char	*pwd;

	pwd = fs_get_cur_dir_name();
	if (!pwd)
		return (-1);
	ft_dprintf(cmd->fds[FD_OUT], "%s\n", pwd);
	return (0);
}
