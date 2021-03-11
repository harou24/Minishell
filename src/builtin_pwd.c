#include "bash_ops.h"
#include "env_access.h"
#include "ft_printf.h"

int	builtin_pwd(t_command *cmd)
{
	char	*current;

	current = env_get_current_dir();
	ft_dprintf(cmd->fds[FD_OUT], "%s\n", current);
	return (0);
}
