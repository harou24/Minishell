#include "bash_ops.h"
#include "env_access.h"
#include "filesystem_traversal.h"
#include "filesystem.h"
#include "ft_printf.h"
#include "path.h"
#include <stdlib.h>
#include <limits.h>

int 	__go_to_prev_dir(void)
{
	return (fs_change_dir(env_get_prev_dir()));
}

int	__go_to_home(void)
{
	return (fs_change_dir(env_get_home()));
}

int	__go_to_path(const char *path)
{
	return (fs_change_dir(path));
}

void	__print_cur_path(void)
{
	ft_dprintf(STDOUT, "%s\n", env_get_current_dir());
}
