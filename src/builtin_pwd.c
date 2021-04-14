#include "bash_ops.h"
#include "env_access.h"
#include "ft_printf.h"
#include "filesystem.h"
#include "filesystem_traversal.h"

int	builtin_pwd(t_command *cmd)
{
	char	*pwd;

	pwd = env_get_current_dir();
	if (!pwd)
		return (2);
	ft_printf("%s\n", pwd);
	return (0);
	(void)cmd;
}
