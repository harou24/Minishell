#include "bash_ops.h"
#include "env_access.h"
#include "ft_printf.h"

int	builtin_pwd(t_command *cmd)
{
	char *current;
	(void)cmd;

	current = env_get_current_dir();
	ft_dprintf(STDERR, "%s\n", current);
	return (0);
}
