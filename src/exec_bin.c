#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "libft.h"
#include "debugger.h"

#include "filesystem.h"
#include "env_access.h"
#include "bash_ops.h"
#include "path.h"

int	exec_bin(t_command *cmd)
{
	extern char	**environ;
	char		*abspath;

	if (strncmp(cmd->path, "./", 2) == 0 || strncmp(cmd->path, "/", 1) == 0)
		abspath = cmd->path;
	else
		abspath = path_expand(env_get_path(), cmd->path);
	if (abspath && file_is_executable(abspath))
	{
		execve(abspath, cmd->argv->argv, environ);
		dbg("execve failed for %s with error : %s\n", abspath, strerror(errno));
		exit (1);
	}
	exit(127);
}
